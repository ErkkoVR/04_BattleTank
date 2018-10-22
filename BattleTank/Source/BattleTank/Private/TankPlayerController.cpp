// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControllerTank(); 
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()) );

	}
	UE_LOG(LogTemp, Warning, TEXT("Player Controller beging play"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	// UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking every s"));
}



ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControllerTank()) { return;  }

	FVector HitLocation; // Out parameter
	
	if (GetSightRayHitLocation(HitLocation))	// Has side effect of actually line-tracing 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString())
		// TODO tank to actually aim at this position

	}



	// get world location through cross-hair
	// if it hits something in the landscape
	    // Tell the controlled tank to aim at this point 
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	// trace from starting location until hit with the unreal object thingy
	// return what was hit as part of the hitlocation fvector
	return true;
}
