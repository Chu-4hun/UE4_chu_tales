// chu_game, All Rights Reserved


#include "ChT_CharacterBase.h"

#include "Components/ChT_CharacterMovementComponent.h"
#include "Components/ChT_HealthComponent.h"
#include "Components/ChT_WeaponComponent.h"


DEFINE_LOG_CATEGORY_STATIC(CharacterBaseLog, All, All);
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

void AChT_CharacterBase::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AChT_CharacterBase::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AChT_CharacterBase::OnStartRunning()
{
	WantsToRun = true;
}

void AChT_CharacterBase::OnEndRunning()
{
	WantsToRun = false;
}

bool AChT_CharacterBase::IsRunning() 
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}