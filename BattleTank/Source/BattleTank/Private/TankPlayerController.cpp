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
	UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking every s"));
}



ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControllerTank()) { return;  }

	// get world location through cross-hair
	// if it hits something in the landscape
	    // Tell the controlled tank to aim at this point 
}
