#include "Fire.h"
#include "Meat.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

AFire::AFire()
{
    PrimaryActorTick.bCanEverTick = true;

    // �g���K�[�{�b�N�X�̐ݒ�
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // Overlap�C�x���g��ݒ�
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFire::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFire::OnOverlapEnd);
}

void AFire::BeginPlay()
{

    Super::BeginPlay();
}

void AFire::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Overlap�J�n���̏���
void AFire::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{


    AMeat* Meat = Cast<AMeat>(OtherActor);
    if (Meat)
    {
        //// �΂ɐG�ꂽ��5�b���Cooked��Ԃɂ���^�C�}�[���J�n
        //GetWorld()->GetTimerManager().SetTimer(CookTimerHandle, [Meat, this]()
        //    {
        //        Meat->ChangeMeatState(EMeatState::Cooked);

        //        // Cooked��ԂɂȂ�����A�����20�b���Burnt��Ԃɂ���^�C�}�[
        //        GetWorld()->GetTimerManager().SetTimer(BurnTimerHandle, [Meat]()
        //            {
        //                Meat->ChangeMeatState(EMeatState::Burnt);
        //            }, 20.0f, false);

        //    }, 5.0f, false);

    }
}

// Overlap�I�����̏���
void AFire::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

    AMeat* Meat = Cast<AMeat>(OtherActor);
    if (Meat)
    {



        // �΂��痣�ꂽ�炷�ׂẴ^�C�}�[���~
        GetWorld()->GetTimerManager().ClearTimer(CookTimerHandle);
        GetWorld()->GetTimerManager().ClearTimer(BurnTimerHandle);

        // ��Ԃ����Z�b�g����ꍇ�͈ȉ���ǉ�
        // Meat->ChangeMeatState(EMeatState::Raw);
    }
}

void AFire::StopCookingTimers()
{
    GetWorld()->GetTimerManager().ClearTimer(CookTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(BurnTimerHandle);
}