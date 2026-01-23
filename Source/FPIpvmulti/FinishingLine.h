// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishingLine.generated.h"
class UBoxComponent;

UCLASS()
class FPIPVMULTI_API AFinishingLine : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishingLine();

protected:
	virtual void BeginPlay() override;

	// Box para detectar jugadores
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* TriggerBox;

	// Variables del servidor
	bool bRaceEnded = false;
	APlayerController* WinnerPC = nullptr;

	// Función cuando se overlappea
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// Lógica solo servidor
	UFUNCTION(Server, Reliable)
	void ServerPlayerReached(APlayerController* PC);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
