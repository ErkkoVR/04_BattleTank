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

ATank* ATankPlayerController::GetControllerTank() const
{
	
	return Cast<ATank>(GetPawn());

}

