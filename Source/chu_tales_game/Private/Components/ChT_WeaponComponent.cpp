// chu_game, All Rights Reserved


#include "Components/ChT_WeaponComponent.h"

#include "ChT_BaseWeapon.h"
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
	if (!Cast<ACharacter>(GetOwner()))return;

	CurrentWeapon = GetWorld()->SpawnActor<AChT_BaseWeapon>(WeaponClass);
	ACharacter* CharaterOwner = Cast<ACharacter>(GetOwner());
	
	if (!CurrentWeapon)return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(CharaterOwner->GetMesh(), AttachmentRules, BoneName); //"hand_r_weapon"
}


void UChT_WeaponComponent::Attack()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->Attack();
}
