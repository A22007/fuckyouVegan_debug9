#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Fire.generated.h"

UCLASS()
class FUCKYOUVEGAN7_API AFire : public AActor
{
    GENERATED_BODY()

public:
    AFire();
    // タイマーを停止する関数
    void StopCookingTimers();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // トリガーボックス
    UPROPERTY(VisibleAnywhere)
        UBoxComponent* TriggerBox;

    // Overlapイベント
    UFUNCTION(BlueprintCallable)
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
        void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    // タイマーのハンドル
    FTimerHandle CookTimerHandle;
    FTimerHandle BurnTimerHandle;
};