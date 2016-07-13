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
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Trigger Volume not found on %s, please select one!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOnPressurePlate() >= MassToOpenDoor)
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


float UOpenDoor::GetTotalMassOnPressurePlate()
{
	if (!PressurePlate) return 0.f;

	TArray<AActor*> PressurePlateActors;
	PressurePlate->GetOverlappingActors(PressurePlateActors);

	float TotalMass = 0.f;
	for (AActor* Actor : PressurePlateActors)
	{
		TotalMass += Actor->GetRootPrimitiveComponent()->GetMass();
	}

	return TotalMass;
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

