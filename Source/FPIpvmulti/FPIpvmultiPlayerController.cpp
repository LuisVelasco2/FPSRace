// Fill out your copyright notice in the Description page of Project Settings.


#include "FPIpvmultiPlayerController.h"

void AFPIpvmultiPlayerController::Client_ShowWinMessage_Implementation()
{
	if (!IsLocalController()) return;

	GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Green,
		TEXT("Lograste escapar.")
	);
}

void AFPIpvmultiPlayerController::Client_ShowLoseMessage_Implementation()
{
	if (!IsLocalController()) return;

	GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Red,
		TEXT("No has escapado.")
	);
}
