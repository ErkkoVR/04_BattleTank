// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
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
	  // UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString())
		// TODO tank to actually aim at this position
		GetControllerTank()->AimAt(HitLocation);
	}



	// get world location through cross-hair
	// if it hits something in the landscape
	    // Tell the controlled tank to aim at this point 
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// OutHitLocation = FVector(1.0);
	// trace from starting location until hit with the unreal object thingy
	// return what was hit as part of the hitlocation fvector

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("the screenlocation is: %s"), *ScreenLocation.ToString())

	// de-project the screen position of crosshair to a world direction
	FVector LookDirection;
	FVector StartLocation;
	if (GetLookDirection(ScreenLocation, LookDirection, StartLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction is: %s"), *LookDirection.ToString())
		// line-trace along that look direction, see what we hit

		GetLookVectorHitLocation(LookDirection, StartLocation, OutHitLocation);

	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector StartLocation, FVector& HitLocation) const
{
	FHitResult HitResult;
	// auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	// UE_LOG(LogTemp, Warning, TEXT("the Endlocation is as follows: %s"), *EndLocation.ToString())
	// UE_LOG(LogTemp, Warning, TEXT("the startlocation is as follows: %s"), *StartLocation.ToString())

	const static FName Tag = TEXT("MyTag");
	//GetWorld()->DebugDrawTraceTag = Tag;
	//FCollisionQueryParams Params(Tag);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetControllerTank());
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility, CollisionParams)
		)
	{
		HitLocation = HitResult.Location;
		auto name = HitResult.ToString();
		// UE_LOG(LogTemp, Warning, TEXT("name of thing being hit: %s"), *name)
		// UE_LOG(LogTemp, Warning, TEXT("inside getlookvectorhitlocation we are getting: %s"), *HitLocation.ToString())

		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& StartLocation) const
{
	// FVector WorldLocation;
	// FVector WorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, StartLocation, LookDirection); 

}