// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChT_SwordBase.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "ChT_WeaponComponent.generated.h"


class AChT_BaseCharacter;
class AChT_BaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHU_TALES_GAME_API UChT_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChT_WeaponComponent();
	
	UFUNCTION()
	void Attack();


protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AChT_SwordBase> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName SocketName = "hand_r_weapon";


	

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AChT_SwordBase* CurrentWeapon;

	UFUNCTION()
	float PlayAttackAnim();

	UFUNCTION()
	void OnSwingEnd();

	FTimerHandle TimerHandler;


	void SpawnWeapon();
};
