// chu_game, All Rights Reserved


#include "Components/ChT_HealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

// Sets default values for this component's properties
UChT_HealthComponent::UChT_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UChT_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UChT_HealthComponent::OnTakeAnyDamage);
	}
	
}


void UChT_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                           AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() ) return;
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal.bAutoHealIsEnable)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UChT_HealthComponent::HealUpdate,
		                                       AutoHeal.HealUpdateTime, true, AutoHeal.TimeToStartAutoHeal);
	}
	// UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f Damage causer: %s"), Damage, *DamageCauser->GetName());
}

void UChT_HealthComponent::HealUpdate()
{
	SetHealth(Health + AutoHeal.HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UChT_HealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
