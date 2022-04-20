// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
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
	
	
	virtual void BeginPlay() override;
};