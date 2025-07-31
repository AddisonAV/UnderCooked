// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CharacterInterface.h"
#include "Interfaces/InteractInterface.h"
#include "Structs/InteractStructs.h"
#include "BaseCharacter.generated.h"

class UWidgetComponent;
class UInputAction;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class UNDERCOOKED_API ABaseCharacter : public ACharacter, public ICharacterInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ICharacterInterface implementation
	virtual void GatherCharacterValues(bool& bOutIsMoving, float& OutSpeed, FVector& OutDirection) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	void DoMove(float Right, float Forward);

	void ToggleSprint(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);
	void InteractOngoing(const FInputActionValue& Value);
	void InteractCompleted(const FInputActionValue& Value);
	

private:

	// IInteractInterface implementation
	virtual void AddInteractableActor(AInteractableActor* InteractableActor) override;
	virtual void RemoveInteractableActor(AInteractableActor* InteractableActor) override;
	
/* ------------------ Proprieties ------------------ */

protected:
	

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SprintAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* InteractAction = nullptr;


	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidgetComponent* InteractionProgress = nullptr;
	
private:

	UPROPERTY()
	AInteractableActor* CurrentInteractableActor = nullptr; // The currently interactable actor, if any

	FCurrentInteraction CurrentInteraction = FCurrentInteraction(); // Current interaction state
	
};
