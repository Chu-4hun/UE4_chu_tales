// chu_game, All Rights Reserved


#include "Components/ChT_CharacterMovementComponent.h"

#include "Player/ChT_BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterMovementComponent, All, All);

float UChT_CharacterMovementComponent::GetMaxSpeed() const
{
	AChT_BaseCharacter* Owner =Cast<AChT_BaseCharacter>(GetPawnOwner());
	const float MaxSpeed = Super::GetMaxSpeed();
	return Owner && Owner->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
