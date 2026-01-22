// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPIpvmultiGameMode.h"
#include "FPIpvmultiCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FPIpvmultiPlayerController.h"

AFPIpvmultiGameMode::AFPIpvmultiGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AFPIpvmultiGameMode::PlayerWon(AFPIpvmultiCharacter* Winner)
{
	if (bGameEnded || !Winner) return;
	bGameEnded = true;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		AFPIpvmultiPlayerController* MyPC =
			Cast<AFPIpvmultiPlayerController>(PC);

		if (!MyPC) continue;

		if (PC == Winner->GetController())
		{
			MyPC->Client_ShowWinMessage();
		}
		else
		{
			MyPC->Client_ShowLoseMessage();
		}
	}
}
