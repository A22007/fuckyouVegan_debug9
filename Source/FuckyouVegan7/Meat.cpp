#include "Meat.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"  // トリガーボックス用のヘッダー
#include "Fire.h" // Fireクラスをインクルード (火のオブジェクトのクラス名に合わせてください)
#include "Engine/Engine.h"  // UE_LOGに必要

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

    // トリガーボックスの設定
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // デバッグログの出力
    UE_LOG(LogTemp, Error, TEXT("AMeat Constructor Called: MeshComponent initialized"));
}

void AMeat::BeginPlay()
{
    Super::BeginPlay();

    // トリガーボックスのオーバーラップイベントをバインド
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

        // RawからCookedへの遷移
        if (MeatState == EMeatState::Raw && CookingTime >= 10.0f)
        {
            ChangeMeatState(EMeatState::Cooked);
            CookingTime = 0.0f;  // 次のステージに備えてCookingTimeをリセット
        }
        // CookedからBurntへの遷移
        else if (MeatState == EMeatState::Cooked && CookingTime >= 10.0f)
        {
            ChangeMeatState(EMeatState::Undercooked);
            CookingTime = 0.0f;  // 次のステージに備えてCookingTimeをリセット
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
    if (OtherActor->IsA(AFire::StaticClass())) // 火オブジェクトか確認
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


    // OtherActorがAFireクラスのインスタンスか確認
    AFire* Fire = Cast<AFire>(OtherActor);
    if (Fire)
    {
        // 火から離れたらタイマーを停止
        Fire->StopCookingTimers();

        bIsInFire = false;
        //CookingTime = 0.0f; // 火から離れたら時間をリセット
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Exited Fire Area"));
        }
    }
}