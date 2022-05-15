// chu_game, All Rights Reserved


#include "ChT_SwordBase.h"

#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(SwordLog, All, All);

// Sets default values
AChT_SwordBase::AChT_SwordBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sword_mesh");
	StaticMesh->SetupAttachment(GetRootComponent());

	// BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box_collision");
	// BoxCollision->SetCollisionProfileName("SwordCollision");
	// BoxCollision->SetupAttachment(StaticMesh);
	//
	// BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AChT_SwordBase::OnOverlapBegin);
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AChT_SwordBase::OnOverlapBegin);
}

void AChT_SwordBase::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}


void AChT_SwordBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	const AActor* SwordOwner = GetOwner();
	
	if (OtherActor == SwordOwner || OtherActor->GetClass()->IsChildOf(AChT_SwordBase::StaticClass()))return;
	if (CanDealDamage)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red,
		                                 FString::Printf(
			                                 TEXT("Deal damage: %f to %s"), Damage, *OtherActor->GetName()));
		DealDamageToActor(OtherActor, Damage);
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			CanDealDamage = true;
		}, CoolDown, false);
	}
}

// Called when the game starts or when spawned
void AChT_SwordBase::BeginPlay()
{
	Super::BeginPlay();
}

void AChT_SwordBase::DealDamageToActor(AActor* Other, float DealDamage)
{
	const TSubclassOf<UDamageType> DmgTypeClass = UDamageType::StaticClass();
	Other->TakeDamage(DealDamage, FDamageEvent(DmgTypeClass), nullptr, this);
	CanDealDamage = false;
}
