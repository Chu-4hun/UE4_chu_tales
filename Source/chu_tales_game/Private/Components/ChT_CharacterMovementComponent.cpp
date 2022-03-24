// chu_game, All Rights Reserved


#include "Components/ChT_CharacterMovementComponent.h"

#include "Player/ChT_BaseCharacter.h"

float UChT_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AChT_BaseCharacter* Player = Cast<AChT_BaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
