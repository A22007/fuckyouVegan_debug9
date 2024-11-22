#include "Fire.h"
#include "Meat.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

AFire::AFire()
{
    PrimaryActorTick.bCanEverTick = true;

    // トリガーボックスの設定
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // Overlapイベントを設定
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

// Overlap開始時の処理
void AFire::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{


    AMeat* Meat = Cast<AMeat>(OtherActor);
    if (Meat)
    {
        //// 火に触れたら5秒後にCooked状態にするタイマーを開始
        //GetWorld()->GetTimerManager().SetTimer(CookTimerHandle, [Meat, this]()
        //    {
        //        Meat->ChangeMeatState(EMeatState::Cooked);

        //        // Cooked状態になった後、さらに20秒後にBurnt状態にするタイマー
        //        GetWorld()->GetTimerManager().SetTimer(BurnTimerHandle, [Meat]()
        //            {
        //                Meat->ChangeMeatState(EMeatState::Burnt);
        //            }, 20.0f, false);

        //    }, 5.0f, false);

    }
}

// Overlap終了時の処理
void AFire::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

    AMeat* Meat = Cast<AMeat>(OtherActor);
    if (Meat)
    {



        // 火から離れたらすべてのタイマーを停止
        GetWorld()->GetTimerManager().ClearTimer(CookTimerHandle);
        GetWorld()->GetTimerManager().ClearTimer(BurnTimerHandle);

        // 状態をリセットする場合は以下を追加
        // Meat->ChangeMeatState(EMeatState::Raw);
    }
}

void AFire::StopCookingTimers()
{
    GetWorld()->GetTimerManager().ClearTimer(CookTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(BurnTimerHandle);
}