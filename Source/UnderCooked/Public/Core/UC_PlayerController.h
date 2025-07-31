// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UC_PlayerController.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class UNDERCOOKED_API AUC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AUC_PlayerController();

	virtual void BeginPlay() override;

protected:

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	
/*  ------------------ Proprieties ------------------ */

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<UInputMappingContext*> DefaultMappingContexts;
};
