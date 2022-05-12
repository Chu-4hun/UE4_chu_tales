// chu_game, All Rights Reserved


#include "ChT_CharacterBase.h"

#include "Components/ChT_CharacterMovementComponent.h"
#include "Components/ChT_HealthComponent.h"
#include "Components/ChT_WeaponComponent.h"

// Sets default values
AChT_CharacterBase::AChT_CharacterBase(const FObjectInitializer& ObjInit): Super(
	ObjInit.SetDefaultSubobjectClass<UChT_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UChT_HealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UChT_WeaponComponent>("Weapon Component");
}

// Called when the game starts or when spawned
void AChT_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth());
}


void AChT_CharacterBase::OnDeath()
{
}

void AChT_CharacterBase::OnHealthChanged(float Health)
{
}

// Called every frame
void AChT_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
