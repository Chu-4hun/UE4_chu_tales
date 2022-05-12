// chu_game, All Rights Reserved


#include "Components/ChT_CharacterMovementComponent.h"

#include "Player/ChT_PlayerCharacter.h"


DEFINE_LOG_CATEGORY_STATIC(CharacterMovementComponent, All, All);

float UChT_CharacterMovementComponent::GetMaxSpeed() const
{
	AChT_PlayerCharacter* Owner =Cast<AChT_PlayerCharacter>(GetPawnOwner());
	const float MaxSpeed = Super::GetMaxSpeed();
	return Owner && Owner->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
