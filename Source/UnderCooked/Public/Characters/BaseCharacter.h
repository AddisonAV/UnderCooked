// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CharacterInterface.h"
#include "BaseCharacter.generated.h"

class UWidgetComponent;
class UInputAction;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class UNDERCOOKED_API ABaseCharacter : public ACharacter, public ICharacterInterface
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
	
/* ------------------ Proprieties ------------------ */

protected:
	

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SprintAction = nullptr;


	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera = nullptr;

	/* * Interaction Progress Widget
	 * This widget is used to show the progress of an interaction, such as cooking or serving a dish.
	 * It is attached to the character and will be visible when the character is interacting with an object.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> InteractionProgressWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidgetComponent* InteractionProgress = nullptr;
	
private:

	

	
	
};
