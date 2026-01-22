// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPIpvmultiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPIPVMULTI_API AFPIpvmultiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(Client, Reliable)
	void Client_ShowWinMessage();
	
	UFUNCTION(Client, Reliable)
	void Client_ShowLoseMessage();
};
