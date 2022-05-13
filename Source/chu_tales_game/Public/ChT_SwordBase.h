// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ChT_SwordBase.generated.h"

UCLASS()
class CHU_TALES_GAME_API AChT_SwordBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChT_SwordBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackMontage; //Refactor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f ))
	float CoolDown = 0.0f;

	virtual void SetOwner(AActor* NewOwner) override;

	bool CanDealDamage = false;

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f ))
	float Damage = 0.0f;


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);


	virtual void BeginPlay() override;

private:
	
	void DealDamageToActor(AActor* Other, float DealDamage);
};
