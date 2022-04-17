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

	const auto Weapon = GetWorld()->SpawnActor<AChT_BaseWeapon>(WeaponClass);
	ACharacter* CharaterOwner = Cast<ACharacter>(GetOwner());
    if (Weapon)
    {
	    FAttachmentTransformRules AttachmentRules (EAttachmentRule::SnapToTarget, false);
    	Weapon->AttachToComponent(CharaterOwner->GetMesh(),AttachmentRules,"hand_r_weapon");
    }
}
