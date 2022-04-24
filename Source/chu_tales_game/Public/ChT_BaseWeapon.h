// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ChT_BaseWeapon.generated.h"

UCLASS()
class CHU_TALES_GAME_API AChT_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AChT_BaseWeapon();

	virtual void Attack();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Components")
	UBoxComponent* WeaponCollider;
	
	FActorBeginOverlapSignature OverlapSignature;
	
	virtual void BeginPlay() override;

private:
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};