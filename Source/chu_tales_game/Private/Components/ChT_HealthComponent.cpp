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

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UChT_HealthComponent::OnTakeAnyDamage);
	}
}


void UChT_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                           AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	// UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f Damage causer: %s"), Damage, *DamageCauser->GetName());

}
