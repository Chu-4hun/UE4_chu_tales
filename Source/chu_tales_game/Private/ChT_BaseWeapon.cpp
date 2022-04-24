// chu_game, All Rights Reserved


#include "ChT_BaseWeapon.h"

#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

AChT_BaseWeapon::AChT_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>("Collider");
	// WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// WeaponCollider->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	WeaponCollider->SetupAttachment(GetRootComponent());
	

}

void AChT_BaseWeapon::Attack()
{
	UE_LOG(BaseWeaponLog, Display, TEXT("Attack!"));
}

void AChT_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollider->OnComponentHit.AddDynamic(this, &AChT_BaseWeapon::OnOverlap);
}

void AChT_BaseWeapon::OnOverlap(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(BaseWeaponLog, Display, TEXT("Overlap with %s"), *OtherActor->GetName());
}




