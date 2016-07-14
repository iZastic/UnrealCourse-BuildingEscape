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
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
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

