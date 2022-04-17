// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChT_WeaponComponent.generated.h"


class AChT_BaseWeapon;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHU_TALES_GAME_API UChT_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChT_WeaponComponent();

protected:
	UPROPERTY(EditDefaultsonly, Category = "Weapon")
	TSubclassOf<AChT_BaseWeapon> WeaponClass;

	virtual void BeginPlay() override;

private:
	void SpawnWeapon();
};
