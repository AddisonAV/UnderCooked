// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/UC_GameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UUC_GameInstance::Init()
{
	Super::Init();
}


void UUC_GameInstance::MakeHostingServer(APlayerController* PlayerController)
{
	// Player leaves menu level
	bInLobbyScreen = false;
	
	UGameplayStatics::OpenLevel(PlayerController, "Lvl_Restaurant", true, "listen");
}

void UUC_GameInstance::JoinGame(APlayerController* PlayerController, const FString& Address)
{
	// Player leaves menu level
	bInLobbyScreen = false;
	
	// tell client to follow the server
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

