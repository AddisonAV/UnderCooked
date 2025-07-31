// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/BoxComponent.h"
#include "Interfaces/InteractInterface.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetVisibility(true);
	InteractionBox->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	// bind Overlap with the interaction box
	if (InteractionBox)
	{
		InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnOverlapBegin);
		InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnOverlapEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' InteractionBox is not set!"), *GetNameSafe(this));
	}
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// Check if the OtherActor implements the IInteractInterface
		// and if so, call the AddInteractableActor function
		if (IInteractInterface* InteractableInterface = Cast<IInteractInterface>(OtherActor))
		{
			InteractableInterface->AddInteractableActor(this);
		}
	}
}

void AInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		// Check if the OtherActor implements the IInteractInterface
		// and if so, call the RemoveInteractableActor function
		if (IInteractInterface* InteractableInterface = Cast<IInteractInterface>(OtherActor))
		{
			InteractableInterface->RemoveInteractableActor(this);
		}
	}
	
}

