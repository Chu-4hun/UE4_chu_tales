// chu_game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

UCLASS()
class CHU_TALES_GAME_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetInputMode(const FInputModeDataBase& InData);
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AActor*> Pawns;

	int32 CurrentPawnIndex = 0;

	void ChangePawn();
};
