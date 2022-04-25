// chu_game, All Rights Reserved


#include "ChT_SwordBase.h"

// Sets default values
AChT_SwordBase::AChT_SwordBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sword_mesh");
	StaticMesh->SetupAttachment(GetRootComponent());

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box_collision");
	BoxCollision->SetCollisionProfileName("SwordCollision");
	BoxCollision->SetupAttachment(StaticMesh);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AChT_SwordBase::OnOverlapBegin);
}

void AChT_SwordBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	// OtherActor->TakeDamage(Damage,,,this);

	//CoolDown Check
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red,
	                                 FString::Printf(
		                                 TEXT("Deal damage: %f"), Damage));
}

// Called when the game starts or when spawned
void AChT_SwordBase::BeginPlay()
{
	Super::BeginPlay();
}
