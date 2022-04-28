// chu_game, All Rights Reserved


#include "Components/ChT_WeaponComponent.h"

#include "GameFramework/Character.h"
#include "Player/ChT_BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(WeaponComponetLog, All, All);

UChT_WeaponComponent::UChT_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UChT_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	EquipWeapon();
}


void UChT_WeaponComponent::SpawnWeapon(FName InputSocet)
{
	if (!GetWorld()) return;
	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	CurrentWeapon = GetWorld()->SpawnActor<AChT_SwordBase>(WeaponClass); // Refactor This!!!

	if (!CurrentWeapon)return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, InputSocet); 
}


void UChT_WeaponComponent::EquipWeapon()
{
	SpawnWeapon(HandSocketName);
}

void UChT_WeaponComponent::DeEquipWeapon()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("Detroy"));
	
	
	CurrentWeapon->Destroy(); // not Working
	SpawnWeapon(BackSocketName);
}



void UChT_WeaponComponent::Attack()
{
	if (!FMath::IsNearlyZero(CurrentCoolDown))return;
	Cast<AChT_BaseCharacter>(GetOwner())->bIsUpperBody = true;
	EquipWeapon();
	float Delay = PlayAttackAnim();

	UE_LOG(WeaponComponetLog, Display, TEXT("Delay %f"), Delay);

	GetWorld()->GetTimerManager().SetTimer(AnimTimerHandler, this, &UChT_WeaponComponent::OnSwingEnd, Delay,
	                                       false, Delay);
	CurrentCoolDown = CurrentWeapon->CoolDown;
	GetWorld()->GetTimerManager().SetTimer(CoolDownTimerHandler, this, &UChT_WeaponComponent::OnCoolDownEnd,
	                                       CurrentCoolDown,
	                                       false, CurrentCoolDown);
	GetWorld()->GetTimerManager().SetTimer(DeEquipTimerHandler, this, &UChT_WeaponComponent::OnDeEquipTimer,
	                                       TimeToDeEquip,
	                                       false, TimeToDeEquip);
}


float UChT_WeaponComponent::PlayAttackAnim()
{
	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	return CharacterOwner->PlayAnimMontage(CurrentWeapon->AttackMontage, 1, NAME_None);
}

void UChT_WeaponComponent::OnSwingEnd()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("Swing end!"));
	Cast<AChT_BaseCharacter>(GetOwner())->bIsUpperBody = false;
	GetWorld()->GetTimerManager().ClearTimer(AnimTimerHandler);;
}

void UChT_WeaponComponent::OnCoolDownEnd()
{
	CurrentCoolDown = 0.0f;
}

void UChT_WeaponComponent::OnDeEquipTimer()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("DeEquip!"));
	DeEquipWeapon();
}
