﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Characters/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "Actors/InteractableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, InteractionProgress);
	DOREPLIFETIME(ABaseCharacter, CurrentInteraction);
	DOREPLIFETIME(ABaseCharacter, ReplicatedInteractionProgress);
}

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bReplicates = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(80.f, 220.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetRelativeLocation(FVector(-1000.0f, 0.0f, 2400.0f));
	FollowCamera->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	// Create the interaction progress widget
	InteractionProgress = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionProgress"));
	InteractionProgress->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ABaseCharacter::ToggleSprint);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABaseCharacter::Interact);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ABaseCharacter::InteractOngoing);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ABaseCharacter::InteractCompleted);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Canceled, this, &ABaseCharacter::InteractCompleted);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABaseCharacter::GatherCharacterValues(bool& bOutIsMoving, float& OutSpeed, FVector& OutDirection)
{
	// Gather character values
	bOutIsMoving = GetCharacterMovement()->IsMovingOnGround() && !GetVelocity().IsZero();
	OutSpeed = GetVelocity().Size();
	OutDirection =  GetVelocity().GetSafeNormal();
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ABaseCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ABaseCharacter::ToggleSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		if (GetCharacterMovement()->MaxWalkSpeed == 500.f)
		{
			GetCharacterMovement()->MaxWalkSpeed = 800.f; // Sprint speed
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.f; // Walk speed
		}
	}
}

void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	if (CurrentInteractableActor != nullptr)
	{
		if (HasAuthority())
		{
			// Server processes interaction directly
			ProcessInteraction(CurrentInteractableActor);
		}
		else
		{
			// Client: update local interaction for immediate feedback
			ProcessInteraction(CurrentInteractableActor); 
			// Client sends interaction request to the server
			ServerProcessInteraction(CurrentInteractableActor);
		}
	}
}

void ABaseCharacter::InteractOngoing(const FInputActionValue& Value)
{
	if (CurrentInteraction.bTimedInteract)
	{
		// Disable movement while interacting with timed interactable actors
		GetCharacterMovement()->DisableMovement();
		
		float Progress = (FPlatformTime::Seconds() - CurrentInteraction.InteractionStartTime) / CurrentInteraction.InteractionDuration;
		// Check if widget implements interface

		if (HasAuthority())
		{
			ReplicatedInteractionProgress = Progress;
		}
		else
		{
			ServerInteractOngoing(Progress);
		}

		if (Progress <= 1.0f)
		{
			UUserWidget* Widget = Cast<UUserWidget>(InteractionProgress->GetWidget());
			if (Widget && Widget->Implements<UInteractInterface>())
			{
				Execute_InteractionProgress(Widget, Progress);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("'%s' InteractionWidget does not implement IInteractInterface!"), *GetNameSafe(this));
			}
		}
	}
	
}

void ABaseCharacter::InteractCompleted(const FInputActionValue& Value)
{
	// If the interaction was timed, we need to re-enable movement
	if (CurrentInteraction.bTimedInteract)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); // Re-enable movement
	}
	CurrentInteraction = FCurrentInteraction(); // Reset current interaction

	if (HasAuthority())
	{
		ReplicatedInteractionProgress = 0.f; // Reset progress on the server
	}
	else
	{
		ServerInteractOngoing(0.f); // Reset progress on the client
	}

	UUserWidget* Widget = Cast<UUserWidget>(InteractionProgress->GetWidget());
	if (Widget && Widget->Implements<UInteractInterface>())
	{
		Execute_InteractionProgress(Widget, 0.f); // Reset progress to 0
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("'%s' InteractionWidget does not implement IInteractInterface!"), *GetNameSafe(this));
	}
}

void ABaseCharacter::OnRep_InteractionProgress()
{
	UUserWidget* Widget = Cast<UUserWidget>(InteractionProgress->GetWidget());
	if (Widget && Widget->Implements<UInteractInterface>())
	{
		Execute_InteractionProgress(Widget, ReplicatedInteractionProgress);
	}
}

void ABaseCharacter::ServerInteractOngoing_Implementation(float Progress)
{
	ReplicatedInteractionProgress = Progress;
}

void ABaseCharacter::ServerProcessInteraction_Implementation(AInteractableActor* InteractableActor)
{
	// Validate the interaction on the server
	if (InteractableActor)
	{
		ProcessInteraction(InteractableActor);
	}
}

bool ABaseCharacter::ServerProcessInteraction_Validate(AInteractableActor* InteractableActor)
{
	return true;
}

void ABaseCharacter::ProcessInteraction(AInteractableActor* InteractableActor)
{
	CurrentInteraction.InteractableActor = InteractableActor;
	CurrentInteraction.InteractionStartTime = FPlatformTime::Seconds();
	CurrentInteraction.InteractionDuration = InteractableActor->InteractionDuration;
	CurrentInteraction.bTimedInteract = InteractableActor->bIsTimedInteract;

	// Update replicated progress
	ReplicatedInteractionProgress = 0.0f;
}

void ABaseCharacter::AddInteractableActor(AInteractableActor* InteractableActor)
{
	if (InteractableActor)
	{
		CurrentInteractableActor = InteractableActor;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("'%s' InteractableActor is null!"), *GetNameSafe(this));
	}
}

void ABaseCharacter::RemoveInteractableActor(AInteractableActor* InteractableActor)
{
	if (CurrentInteractableActor == InteractableActor)
	{
		CurrentInteractableActor = nullptr;
	}
}


