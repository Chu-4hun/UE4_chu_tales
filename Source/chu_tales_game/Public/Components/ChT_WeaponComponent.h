// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChT_SwordBase.h"
#include "Components/ActorComponent.h"
#include "ChT_WeaponComponent.generated.h"


class AChT_BaseCharacter;
class AChT_BaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHU_TALES_GAME_API UChT_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChT_WeaponComponent();


protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AChT_SwordBase> WeaponClass;

	UPROPERTY(EditAnywhere,Category = "Weapon")
	FName BoneName = "hand_r_weapon";

	virtual void BeginPlay() override;

	UFUNCTION()
	void Attack();
	

private:
	UPROPERTY()
	AChT_SwordBase* CurrentWeapon;
	

	
	void SpawnWeapon();
};
