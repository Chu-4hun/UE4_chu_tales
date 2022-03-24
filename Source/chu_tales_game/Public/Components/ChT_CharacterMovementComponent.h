// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ChT_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHU_TALES_GAME_API UChT_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Movement", meta = (ClampMin = "1.0", ClampMax = "50.0"))
	float RunModifier = 2.0f;

	virtual float GetMaxSpeed() const override;
};
