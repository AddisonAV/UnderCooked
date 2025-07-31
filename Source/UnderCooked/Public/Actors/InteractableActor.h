// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/InteractStructs.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class UNDERCOOKED_API AInteractableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableActor();
/*/	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
/*/
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
/* ------------------- Proprieties ------------------ */

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsTimedInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDuration = 0.0f; // Default interaction duration

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	UBoxComponent* InteractionBox;
	
};
