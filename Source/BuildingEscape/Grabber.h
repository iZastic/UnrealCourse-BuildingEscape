// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Grabber reach length in meters
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.0", UIMax = "5.0"))
	float MaxReach = 2.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Find and setup attached Physics Handle
	void SetupPhysicsHandle();
	// Find and setup attached Input Component and bind actions
	void SetupInputComponent();
	// Get the start and end vectors of the reach line
	void GetReachLineVectors(FVector&, FVector&) const;
	// Find the first physics body within MaxReach distance
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Raycast and grab what's in reach
	void Grab();
	// Release what we grabbed
	void Release();
};
