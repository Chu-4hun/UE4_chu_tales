// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChT_CharacterBase.generated.h"

class UChT_WeaponComponent;
class UChT_HealthComponent;

UCLASS()
class CHU_TALES_GAME_API AChT_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChT_CharacterBase(const FObjectInitializer& ObjInit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="Animation")
	bool bIsUpperBody = false;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Components")
	UChT_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Components")
	UChT_WeaponComponent* WeaponComponent;

	UFUNCTION()
	virtual void OnDeath();
	UFUNCTION()
	virtual void OnHealthChanged(float Health);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
};
