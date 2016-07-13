// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// Get the player view point
	FVector PlayerLocation;
	FRotator PlayerRotation;
	PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	// Log view point info for debugging
	UE_LOG(LogTemp, Warning, TEXT("Location is %s. Rotation is %s."), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	FVector EndVector = PlayerLocation + PlayerRotation.Vector() * (MaxReach * 100.f);
	DrawDebugDirectionalArrow(
		GetWorld(), 
		PlayerLocation, 
		EndVector, 
		5.f, 
		FColor(255, 0, 0)
	);

	// TODO Raycast to the reach distance

	// TODO Find what we hit
}

 