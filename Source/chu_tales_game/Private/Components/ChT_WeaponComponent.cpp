// chu_game, All Rights Reserved


#include "Components/ChT_WeaponComponent.h"

#include "GameFramework/Character.h"
#include "ChT_CharacterBase.h"

DEFINE_LOG_CATEGORY_STATIC(WeaponComponetLog, All, All);

UChT_WeaponComponent::UChT_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UChT_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterOwner = Cast<ACharacter>(GetOwner());
	SpawnWeapon();
	EquipWeapon();
}


void UChT_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	CurrentWeapon = GetWorld()->SpawnActor<AChT_SwordBase>(WeaponClass);
	if (!CurrentWeapon)return;
}

void UChT_WeaponComponent::SwapWeaponSocket(FName ToInputSocket)
{
	if (!CurrentWeapon)return;
	FDetachmentTransformRules DetachmentRule(EDetachmentRule::KeepWorld, false);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	CurrentWeapon->SetOwner(CharacterOwner);

	if (CurrentWeapon->IsAttachedTo(CharacterOwner))
	{
		CurrentWeapon->DetachFromActor(DetachmentRule);
	}
	CurrentWeapon->AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, ToInputSocket);
}


void UChT_WeaponComponent::EquipWeapon()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("Equipped"));
	bIsEquipped = true;
	SwapWeaponSocket(HandSocketName);
}

void UChT_WeaponComponent::DeEquipWeapon()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("Destroy"));

	bIsEquipped = false;
	SwapWeaponSocket(BackSocketName);
}

void UChT_WeaponComponent::DestroyWeapon()
{
	if (!CurrentWeapon)return;
	CurrentWeapon->Destroy();
}


void UChT_WeaponComponent::Attack()
{
	if (!FMath::IsNearlyZero(CurrentCoolDown))return;

	Cast<AChT_CharacterBase>(CharacterOwner)->bIsUpperBody = true;
	
	if (!bIsEquipped) EquipWeapon(); //Get weapon in hand
	CurrentWeapon->CanDealDamage = true;
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


float UChT_WeaponComponent::PlayAttackAnim() const
{
	return CharacterOwner->PlayAnimMontage(CurrentWeapon->AttackMontage, 1, NAME_None);
}

void UChT_WeaponComponent::OnSwingEnd()
{
	UE_LOG(WeaponComponetLog, Display, TEXT("Swing end!"));
	if (!CurrentWeapon)return;
	Cast<AChT_CharacterBase>(CharacterOwner)->bIsUpperBody = false;
	CurrentWeapon->CanDealDamage = false;
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
