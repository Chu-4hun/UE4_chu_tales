// chu_game, All Rights Reserved


#include "ChT_BaseWeapon.h"


DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

AChT_BaseWeapon::AChT_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void AChT_BaseWeapon::Attack()
{
	UE_LOG(BaseWeaponLog, Display, TEXT("Attack!"));
}

void AChT_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
