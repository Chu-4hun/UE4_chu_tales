// chu_game, All Rights Reserved


#include "ChT_BaseWeapon.h"

AChT_BaseWeapon::AChT_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void AChT_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
