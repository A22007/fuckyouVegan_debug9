#include "Meat.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"  // �g���K�[�{�b�N�X�p�̃w�b�_�[
#include "Fire.h" // Fire�N���X���C���N���[�h (�΂̃I�u�W�F�N�g�̃N���X���ɍ��킹�Ă�������)
#include "Engine/Engine.h"  // UE_LOG�ɕK�v

AMeat::AMeat()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeatState = EMeatState::Raw;
    bIsInFire = false;
    CookingTime = 0.0f;

    if (RawMesh)
    {
        MeshComponent->SetStaticMesh(RawMesh);
    }

    // �g���K�[�{�b�N�X�̐ݒ�
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // �f�o�b�O���O�̏o��
    UE_LOG(LogTemp, Error, TEXT("AMeat Constructor Called: MeshComponent initialized"));
}

void AMeat::BeginPlay()
{
    Super::BeginPlay();

    // �g���K�[�{�b�N�X�̃I�[�o�[���b�v�C�x���g���o�C���h
    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMeat::OnOverlapBegin);
        TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AMeat::OnOverlapEnd);
    }

    EnablePhysics();
}

void AMeat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsInFire)
    {
        CookingTime += DeltaTime;

        // Raw����Cooked�ւ̑J��
        if (MeatState == EMeatState::Raw && CookingTime >= 10.0f)
        {
            ChangeMeatState(EMeatState::Cooked);
            CookingTime = 0.0f;  // ���̃X�e�[�W�ɔ�����CookingTime�����Z�b�g
        }
        // Cooked����Burnt�ւ̑J��
        else if (MeatState == EMeatState::Cooked && CookingTime >= 10.0f)
        {
            ChangeMeatState(EMeatState::Undercooked);
            CookingTime = 0.0f;  // ���̃X�e�[�W�ɔ�����CookingTime�����Z�b�g
        }
        else if (MeatState == EMeatState::Undercooked && CookingTime >= 10.0f)
        {
            ChangeMeatState(EMeatState::Burnt);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("KOGETAAAAAAAAAAAAAAAAAA"));
            }
        }
    }
}

void AMeat::ChangeMeatState(EMeatState NewState)
{
    MeatState = NewState;

    switch (MeatState)
    {
    case EMeatState::Raw:
        if (RawMesh)
        {
            MeshComponent->SetStaticMesh(RawMesh);
        }
        break;
    case EMeatState::Undercooked:
        if (UndercookedMesh)
        {
            MeshComponent->SetStaticMesh(UndercookedMesh);
        }
        break;
    case EMeatState::Cooked:
        if (CookedMesh)
        {
            MeshComponent->SetStaticMesh(CookedMesh);
        }
        break;
    case EMeatState::Burnt:
        if (BurntMesh)
        {
            MeshComponent->SetStaticMesh(BurntMesh);
        }
        break;
    }
}

void AMeat::EnablePhysics()
{
    if (MeshComponent)
    {
        MeshComponent->SetSimulatePhysics(true);
    }
}

void AMeat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(AFire::StaticClass())) // �΃I�u�W�F�N�g���m�F
    {
        bIsInFire = true;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Entered Fire Area"));
        }
    }
}

void AMeat::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


    // OtherActor��AFire�N���X�̃C���X�^���X���m�F
    AFire* Fire = Cast<AFire>(OtherActor);
    if (Fire)
    {
        // �΂��痣�ꂽ��^�C�}�[���~
        Fire->StopCookingTimers();

        bIsInFire = false;
        //CookingTime = 0.0f; // �΂��痣�ꂽ�玞�Ԃ����Z�b�g
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Exited Fire Area"));
        }
    }
}