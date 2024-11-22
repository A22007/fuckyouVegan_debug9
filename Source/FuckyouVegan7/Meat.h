#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"  // �g���K�[�{�b�N�X�p�̃w�b�_�[
#include "Meat.generated.h"  // �Ō�ɔz�u����K�v������܂�

UENUM(BlueprintType)
enum class EMeatState : uint8 {
    Raw     UMETA(DisplayName = "Raw"),
    Undercooked     UMETA(DisplayName = "Undercooked"),
    Cooked  UMETA(DisplayName = "Cooked"),
    Burnt   UMETA(DisplayName = "Burnt")
};

UCLASS()
class FUCKYOUVEGAN7_API AMeat : public AActor
{
    GENERATED_BODY()

public:
    AMeat();

    // �g���K�[�{�b�N�X
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UBoxComponent* TriggerBox;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ���݂̏Ă������̏��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        EMeatState MeatState;

    // ��Ԃ�ύX����֐�
    void ChangeMeatState(EMeatState NewState);

    // �Փˎ��̏���
    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // �Ă��������Ƃ̃��b�V��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        UStaticMesh* RawMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        UStaticMesh* UndercookedMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        UStaticMesh* CookedMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        UStaticMesh* BurntMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        float CookingTime;

private:
    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* MeshComponent;

    // �΂ɐG��Ă��邩�ǂ����̃t���O
    bool bIsInFire;


    // �����V�~�����[�V������L���ɂ���֐�
    void EnablePhysics();
};