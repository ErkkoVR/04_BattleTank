// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControllerTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find AI controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *(ControlledTank->GetName()));

	}
	UE_LOG(LogTemp, Warning, TEXT("AI Controller beging play"));
}

ATank* ATankAIController::GetControllerTank() const
{

	return Cast<ATank>(GetPawn());

}



