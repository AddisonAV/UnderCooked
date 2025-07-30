// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/UC_GameMode.h"

#include "Kismet/GameplayStatics.h"

AUC_GameMode::AUC_GameMode()
{
	// Disabling the tick for the GameMode to improve performance, as it is not needed.
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AUC_GameMode::BeginPlay()
{
	Super::BeginPlay();

	
}