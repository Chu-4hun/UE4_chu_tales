// chu_game, All Rights Reserved


#include "Player/ChT_PlayerCharacter.h"

#include "Components/ChT_CharacterMovementComponent.h"
#include "Components/ChT_WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerCharacterLog, All, All);


// Sets default values
AChT_PlayerCharacter::AChT_PlayerCharacter(const FObjectInitializer& ObjInit):AChT_CharacterBase(ObjInit)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AChT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthTextComponent);
	OnHealthChanged(HealthComponent->GetHealth());

	HealthComponent->OnHealthChanged.AddDynamic(this, &AChT_PlayerCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddDynamic(this, &AChT_PlayerCharacter::OnDeath);
}

void AChT_PlayerCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


// Called every frame
void AChT_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AChT_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &AChT_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChT_PlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AChT_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookAround", this, &AChT_PlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Zoom", this, &AChT_PlayerCharacter::Zoom);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AChT_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AChT_PlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AChT_PlayerCharacter::OnEndRunning);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, WeaponComponent, &UChT_WeaponComponent::Attack);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AChT_PlayerCharacter::Roll);
}

void AChT_PlayerCharacter::Roll()
{
	if (this->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())return;
	WeaponComponent->DeEquipWeapon();
	this->bUseControllerRotationYaw = false;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		this->bUseControllerRotationYaw = true;
	}, PlayAnimMontage(RollAnimMontage), false);
}

void AChT_PlayerCharacter::Zoom(float Amount)
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Amount * -100, 100.0f,
	                                                   600.0f);
}



float AChT_PlayerCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())return 0.0f;
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AChT_PlayerCharacter::OnDeath()
{
	UE_LOG(PlayerCharacterLog, Display, TEXT("Player %s is dead"), *GetName())

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	WeaponComponent->DestroyWeapon();
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
