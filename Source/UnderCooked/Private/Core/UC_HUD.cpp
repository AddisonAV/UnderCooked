// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/UC_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/UC_GameInstance.h"

AUC_HUD::AUC_HUD()
{
	// Disabling the tick for the HUD to improve performance, as it is not needed.
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AUC_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (UUC_GameInstance* GameInstanceRef = Cast<UUC_GameInstance>( GetGameInstance()))
	{
	
		GameInstanceRef->IsInLobbyScreen() ? ShowLobbyWidget() : ShowGameWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UC_HUD::BeginPlay - GameInstance is not of type UUC_GameInstance"));
	}
}
void AUC_HUD::ShowLobbyWidget() const
{
	if (LobbyWidget)
	{
		if (UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), LobbyWidget))
		{
			WidgetInstance->AddToViewport();
		}
	}
}

void AUC_HUD::ShowGameWidget() const
{
	if (GameWidget)
	{
		if (UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameWidget))
		{
			WidgetInstance->AddToViewport();
		}
	}
}
