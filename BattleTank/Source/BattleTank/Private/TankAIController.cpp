// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is targeting  %s"), *(PlayerTank->GetName()));

	}
	UE_LOG(LogTemp, Warning, TEXT("AI Controller beging play"));


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{

		GetControllerTank()->AimAt(GetPlayerTank()->GetActorLocation());
		// AimAtPlayer();

	}	// UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking every s"));
}


ATank* ATankAIController::GetControllerTank() const
{

	return Cast<ATank>(GetPawn());

}

ATank * ATankAIController::GetPlayerTank() const
{
	
	// Get world first, then get actors, from those get the player

	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI could not find player controller"));
		return nullptr;
	}
	else
	{
		return Cast<ATank>(Player); 
	}

}

void ATankAIController::AimAtPlayer() const
{
	auto PlayerTank = GetPlayerTank();
	auto OurTank = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at player in location: %s "),*OurTank , *PlayerTank->GetActorLocation().ToString())

}




