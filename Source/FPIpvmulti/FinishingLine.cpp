// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishingLine.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFinishingLine::AFinishingLine()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AFinishingLine::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishingLine::OnOverlapBegin);
}

void AFinishingLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Solo jugadores (no queremos overlaps falsos)
	APlayerController* PC = Cast<APlayerController>(OtherActor->GetInstigatorController());
	if (!PC) return;

	ServerPlayerReached(PC);
}

void AFinishingLine::ServerPlayerReached_Implementation(APlayerController* PC)
{
	if (!HasAuthority()) return;

	if (!bRaceEnded)
	{
		// Primer jugador -> gana
		bRaceEnded = true;
		WinnerPC = PC;

		PC->ClientMessage(TEXT("GANASTE!")); // Luego tú cambias esto por tu Widget
	}
	else
	{
		// Segundo jugador -> pierde
		PC->ClientMessage(TEXT("PERDISTE!"));
	}
}

void AFinishingLine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFinishingLine, bRaceEnded);
	DOREPLIFETIME(AFinishingLine, WinnerPC);
}



