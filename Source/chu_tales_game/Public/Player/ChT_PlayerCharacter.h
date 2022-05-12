// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"

#include "Components/ChT_HealthComponent.h"
#include "Components/TextRenderComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "ChT_CharacterBase.h"
#include "ChT_PlayerCharacter.generated.h"

class UChT_WeaponsComponent;
class UChT_WeaponComponent;
UCLASS()
class CHU_TALES_GAME_API AChT_PlayerCharacter : public AChT_CharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChT_PlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="Animation")
	UAnimMontage* RollAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Damage")
	float LifeSpanOnDeath = 5.0f;

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;


private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Roll();

	void Zoom(float Amount);

	void OnStartRunning();
	void OnEndRunning();
	
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health) override;
};
