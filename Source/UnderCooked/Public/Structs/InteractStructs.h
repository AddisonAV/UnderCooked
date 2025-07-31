#pragma once

#include "CoreMinimal.h"
#include "InteractStructs.generated.h"

class AInteractableActor;


USTRUCT(BlueprintType)
struct UNDERCOOKED_API FCurrentInteraction
{
	GENERATED_BODY()

public:	
	UPROPERTY()
	AInteractableActor*	InteractableActor;
	bool bTimedInteract;
	double InteractionStartTime;
	float InteractionDuration;

	FCurrentInteraction()
		: InteractableActor(nullptr), bTimedInteract(false), InteractionStartTime(0.0), InteractionDuration(0.0f)
	{
	}

	FCurrentInteraction(AInteractableActor* InInteractableActor, bool bInTimedInteract, double InInteractionStartTime, float InInteractionDuration)
		: InteractableActor(InInteractableActor), bTimedInteract(bInTimedInteract), InteractionStartTime(InInteractionStartTime), InteractionDuration(InInteractionDuration)
	{
	}
};