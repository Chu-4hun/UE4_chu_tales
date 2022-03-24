// chu_game, All Rights Reserved

#include "ChT_GameModeBase.h"

#include "Player/ChT_PlayerController.h"

AChT_GameModeBase::AChT_GameModeBase()
{
	DefaultPawnClass = AChT_PlayerController::StaticClass();
}
