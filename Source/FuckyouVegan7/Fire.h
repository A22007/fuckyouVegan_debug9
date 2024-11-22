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
    // �^�C�}�[���~����֐�
    void StopCookingTimers();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // �g���K�[�{�b�N�X
    UPROPERTY(VisibleAnywhere)
        UBoxComponent* TriggerBox;

    // Overlap�C�x���g
    UFUNCTION(BlueprintCallable)
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
        void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    // �^�C�}�[�̃n���h��
    FTimerHandle CookTimerHandle;
    FTimerHandle BurnTimerHandle;
};