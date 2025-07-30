// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UC_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UNDERCOOKED_API AUC_HUD : public AHUD
{
	GENERATED_BODY()

public:
	
	AUC_HUD();
	virtual void BeginPlay() override;


private:
	
	void ShowLobbyWidget() const;
	void ShowGameWidget() const;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LobbyWidget = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameWidget = nullptr;
};
