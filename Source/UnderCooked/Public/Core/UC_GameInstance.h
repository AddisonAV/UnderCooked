// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Public/Interfaces/ServerInterface.h"
#include "UC_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNDERCOOKED_API UUC_GameInstance : public UGameInstance, public IServerInterface
{
	GENERATED_BODY()

public:

	// IServerInterface implementation
	virtual void MakeHostingServer(APlayerController *PlayerController) override;
	virtual void JoinGame(APlayerController *PlayerController, const FString& Address = "127.0.0.1") override;

	bool IsInLobbyScreen() const { return bInLobbyScreen; }


protected:
	
	// Begin play for game instance classes.
	virtual void Init() override;



	
/* ------------------   Properties   ------------------ */

private:

	bool bInLobbyScreen = true;
protected:
	

};
