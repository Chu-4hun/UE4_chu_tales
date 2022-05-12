// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ChT_SwordBase.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "ChT_WeaponComponent.generated.h"


class AChT_PlayerCharacter;
class AChT_BaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHU_TALES_GAME_API UChT_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChT_WeaponComponent();
	
	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

	UFUNCTION(BlueprintCallable)
	void DeEquipWeapon();

	UFUNCTION(BlueprintCallable)
	void DestroyWeapon();

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AChT_SwordBase> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName HandSocketName = "hand_rSocket";

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName BackSocketName = "neck_01Socket";

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (ClampMin = 0.0f))
	float TimeToDeEquip = 5.0f;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AChT_SwordBase* CurrentWeapon;

	UPROPERTY()
	float CurrentCoolDown = 0.0f;

	UFUNCTION()
	float PlayAttackAnim() const;

	UFUNCTION()
	void OnSwingEnd();

	UFUNCTION()
	void OnCoolDownEnd();

	UFUNCTION()
	void OnDeEquipTimer();

	FTimerHandle AnimTimerHandler;
	FTimerHandle CoolDownTimerHandler;
	FTimerHandle DeEquipTimerHandler;

	UPROPERTY()
	bool bIsEquipped = false;

	UPROPERTY()
	ACharacter* CharacterOwner;


	void SpawnWeapon();
	void SwapWeaponSocket(FName ToInputSocket);
};
