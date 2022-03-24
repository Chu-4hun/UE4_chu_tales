// chu_game, All Rights Reserved


#include "chu_tales_game/Public/SandboxPlayerController.h"

#include "chu_tales_game/Public/SandboxPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(SandboxPlayerController, All, All)

void ASandboxPlayerController::SetInputMode(const FInputModeDataBase& InData)
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("SwitchPawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1)return;

	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	// if (!CurrentPawn)return;
	Possess(CurrentPawn);
	UE_LOG(SandboxPlayerController, Display, TEXT("Change player pawn"))
}
