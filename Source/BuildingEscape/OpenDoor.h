// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

// Create blueprint delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Create the blueprint assignable event variables
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 40.f;

	float GetTotalMassOnPressurePlate();
};
