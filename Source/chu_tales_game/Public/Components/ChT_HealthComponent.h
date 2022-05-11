// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChT_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignsture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSugnature, float, Health);

USTRUCT(BlueprintType)
struct FAutoHeal
{
	GENERATED_BODY();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool bAutoHealIsEnable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta =(EditCondition = "bAutoHealIsEnable"))
	float TimeToStartAutoHeal = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta =(EditCondition = "bAutoHealIsEnable"))
	float HealUpdateTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta =(EditCondition = "bAutoHealIsEnable"))
	float HealModifier = 1.0f;

	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHU_TALES_GAME_API UChT_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UChT_HealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return FMath::IsNearlyZero(Health);};

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignsture OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSugnature OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.0f ))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.0f ))
	FAutoHeal AutoHeal;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                           class AController* InstigatedBy, AActor* DamageCauser);
	
	void HealUpdate();
	void SetHealth(float NewHealth);
};
