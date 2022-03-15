// Copyright Epic Games, Inc. All Rights Reserved.


#include "chu_tales_gameGameModeBase.h"
#include "Public/SandboxPawn.h"
#include "Public/SandboxPlayerController.h"

AChu_tales_gameGameModeBase::AChu_tales_gameGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
