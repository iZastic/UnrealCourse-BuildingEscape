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
	// Calculate end location vector using max reach
	FVector EndLocation = PlayerLocation + PlayerRotation.Vector() * (MaxReach * 100.f);
	
	DrawDebugDirectionalArrow(
		GetWorld(), 
		PlayerLocation, 
		EndLocation, 
		5.f, 
		FColor(255, 0, 0)
	);

	// Line-trace (Raycast) to the reach distance
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams QueryParams(FName(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerLocation, EndLocation, ObjectParams, QueryParams);
	
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Grabber hit %s."), *ActorHit->GetName());
	}

	// TODO Find what we hit
}

 