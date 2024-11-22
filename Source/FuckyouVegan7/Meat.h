#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"  // トリガーボックス用のヘッダー
#include "Meat.generated.h"  // 最後に配置する必要があります

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

    // トリガーボックス
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UBoxComponent* TriggerBox;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // 現在の焼き加減の状態
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meat")
        EMeatState MeatState;

    // 状態を変更する関数
    void ChangeMeatState(EMeatState NewState);

    // 衝突時の処理
    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // 焼き加減ごとのメッシュ
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

    // 火に触れているかどうかのフラグ
    bool bIsInFire;


    // 物理シミュレーションを有効にする関数
    void EnablePhysics();
};