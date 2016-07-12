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
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorsThatCanActivate.Add(GetWorld()->GetFirstPlayerController()->GetPawn());
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	bIsPressurePlateActived = false;
	// Set pressure plate activated if any actors that can activate are overlapping
	for (AActor* Actor : ActorsThatCanActivate)
	{
		if (PressurePlate->IsOverlappingActor(Actor))
		{
			bIsPressurePlateActived = true;
			break;
		}
	}

	if (bIsPressurePlateActived)
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		CloseDoor(DeltaTime);
	}
}


void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator OwnerRotator = GetOwner()->GetActorRotation();
	FRotator DoorCloseRotator(0.f, DoorCloseAngle, 0.f);
	// If the door is not in the fully closed rotation
	if (!OwnerRotator.Equals(DoorCloseRotator))
	{
		// Rotate the door towards the closed rotation
		GetOwner()->SetActorRotation(OwnerRotator.Add(0.f, 270.f * DeltaTime, 0.f));

		// When the door is past the closed angle
		if (OwnerRotator.Yaw >= DoorCloseAngle)
		{
			GetOwner()->SetActorRotation(DoorCloseRotator);
		}
	}
}


void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator OwnerRotator = GetOwner()->GetActorRotation();
	FRotator DoorOpenRotator(0.f, DoorOpenAngle, 0.f);
	// If the door is not in the fully open rotation
	if (!OwnerRotator.Equals(DoorOpenRotator))
	{
		// Rotate the door towards the open rotation
		GetOwner()->SetActorRotation(OwnerRotator.Add(0.f, -180 * DeltaTime, 0.f));

		// When the door is past the open angle
		if (OwnerRotator.Yaw > 0 && OwnerRotator.Yaw < DoorOpenAngle)
		{
			GetOwner()->SetActorRotation(DoorOpenRotator);
		}
	}
}

