// chu_game, All Rights Reserved


#include "Components/ChT_WeaponComponent.h"

#include "GameFramework/Character.h"

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
	if(!Cast<ACharacter>(GetOwner()))return;


	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	CurrentWeapon = GetWorld()->SpawnActor<AChT_SwordBase>(WeaponClass);
	
	if (!CurrentWeapon)return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, BoneName); //"hand_r_weapon"
}


void UChT_WeaponComponent::Attack()
{
	
}

