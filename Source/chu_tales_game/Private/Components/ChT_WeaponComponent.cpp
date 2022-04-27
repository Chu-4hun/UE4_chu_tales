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
	SpawnWeapon();
}


void UChT_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());

	CurrentWeapon = GetWorld()->SpawnActor<AChT_SwordBase>(WeaponClass);

	if (!CurrentWeapon)return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, SocketName); //"hand_r_weapon"
}

void UChT_WeaponComponent::Attack()
{
	
	Cast<AChT_BaseCharacter>(GetOwner())->bIsUpperBody = true;
	float Delay = PlayAttackAnim();
	
	UE_LOG(WeaponComponetLog,Display,TEXT("Delay %f"), Delay);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UChT_WeaponComponent::OnSwingEnd, Delay,
	                                       false, Delay);
}


float UChT_WeaponComponent::PlayAttackAnim()
{
	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	return CharacterOwner->PlayAnimMontage(CurrentWeapon->AttackMontage,1,NAME_None);
}

void UChT_WeaponComponent::OnSwingEnd()
{
	UE_LOG(WeaponComponetLog,Display,TEXT("Swing end!"));
	Cast<AChT_BaseCharacter>(GetOwner())->bIsUpperBody = false;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
}
