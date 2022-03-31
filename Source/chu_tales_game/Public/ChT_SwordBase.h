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

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f ))
	float Damage = 0.0f;

	// CoolDown var needed 

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

	virtual void BeginPlay() override;
};
