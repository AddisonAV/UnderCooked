// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Interfaces/ServerInterface.h"
#include "UC_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNDERCOOKED_API AUC_GameMode : public AGameModeBase, public IServerInterface
{
	GENERATED_BODY()

public:

	AUC_GameMode();
	virtual void BeginPlay() override;


/* ------------------   Properties   ------------------ */

private:

	// List of player controllers in the game mode
	TArray<TObjectPtr<APlayerController>> PlayerControllers;
};
