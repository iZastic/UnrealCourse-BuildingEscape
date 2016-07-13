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
	
	SetupPhysicsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// TODO: Move the object we are holding if physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// Get the player controller
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		// Get the player view point
		FVector PlayerLocation;
		FRotator PlayerRotation;
		PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

		// Calculate end location vector using max reach
		FVector EndLocation = PlayerLocation + PlayerRotation.Vector() * (MaxReach * 100.f);

		PhysicsHandle->SetTargetLocation(EndLocation);
	}
}

void UGrabber::SetupPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s, please add one!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Component not found on %s!"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Get the player view point
	FVector PlayerLocation;
	FRotator PlayerRotation;
	PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	// Calculate end location vector using max reach
	FVector EndLocation = PlayerLocation + PlayerRotation.Vector() * (MaxReach * 100.f);

	// Line-trace (Raycast) to the reach distance
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams QueryParams(FName(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerLocation, EndLocation, ObjectParams, QueryParams);

	return HitResult;
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if (HitResult.bBlockingHit) {
		// TODO: Attach physics handle
		PhysicsHandle->GrabComponent(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, false);
	}
}

void UGrabber::Release()
{
	// TODO: Drop object if physics handle is attached
	PhysicsHandle->ReleaseComponent();
}

 