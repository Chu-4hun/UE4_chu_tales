// chu_game, All Rights Reserved


#include "Player/ChT_BaseCharacter.h"

#include "Components/ChT_CharacterMovementComponent.h"
#include "Components/ChT_WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);


// Sets default values
AChT_BaseCharacter::AChT_BaseCharacter(const FObjectInitializer& ObjInit): Super(
	ObjInit.SetDefaultSubobjectClass<UChT_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UChT_HealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<UChT_WeaponComponent>("Weapon Component");

	
}

// Called when the game starts or when spawned
void AChT_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());

	HealthComponent->OnDeath.AddUObject(this, &AChT_BaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AChT_BaseCharacter::OnHealthChanged);
}

void AChT_BaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


// Called every frame
void AChT_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AChT_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AChT_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChT_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AChT_BaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookAround", this, &AChT_BaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Zoom", this, &AChT_BaseCharacter::Zoom);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AChT_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AChT_BaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AChT_BaseCharacter::OnEndRunning);
	PlayerInputComponent->BindAction("Attack", IE_Pressed,WeaponComponent,&UChT_WeaponComponent::Attack);
}

void AChT_BaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AChT_BaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AChT_BaseCharacter::Zoom(float Amount)
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Amount * -100, 100.0f,
	                                                   600.0f);
}

void AChT_BaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AChT_BaseCharacter::OnEndRunning()
{
	WantsToRun = false;
}


bool AChT_BaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AChT_BaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())return 0.0f;
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AChT_BaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName())
	
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	
}
