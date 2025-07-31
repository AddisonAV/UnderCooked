#pragma once

#include "CoreMinimal.h"

class AInteractableActor;


struct UNDERCOOKED_API FCurrentInteraction
{
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