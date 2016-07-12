// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MyDoorOpenRotator = FRotator(0.f, 80.f, 0.f);
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate->IsOverlappingActor(ActorThatCanActivate))
	{
		// Check if the door is not considered open
		if (!GetOwner()->GetActorRotation().Equals(MyDoorOpenRotator, 10.f)) {
			// Rotate the door towards the open rotation
			GetOwner()->SetActorRotation(GetOwner()->GetActorRotation().Add(0.f, -90.f * DeltaTime, 0.f));
			// Log the values for debugging
			FString OwnerRotation = GetOwner()->GetActorRotation().ToString();
			UE_LOG(LogTemp, Warning, TEXT("Door rotation is %s"), *OwnerRotation);
		}
	}
}

