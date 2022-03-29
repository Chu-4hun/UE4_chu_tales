// chu_game, All Rights Reserved


#include "Components/ChT_HealthComponent.h"

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
}