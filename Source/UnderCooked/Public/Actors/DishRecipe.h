// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "DishRecipe.generated.h"

UCLASS()
class UNDERCOOKED_API ADishRecipe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADishRecipe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


/* ------------------   Properties   ------------------ */

	UPROPERTY()
	FGameplayTagContainer Ingredients; // Tags representing the ingredients required for this dish
	
	
};
