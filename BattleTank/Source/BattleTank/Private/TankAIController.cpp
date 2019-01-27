// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	

	MoveToActor(PlayerTank, AcceptanceRadius);

		// UE_LOG(LogTemp, Warning, TEXT("%s AI Controlled Tank has called with %s"), *ControlledTank->GetName(), AcceptanceRadius)

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// ControlledTank->AimAt(PlayerTank->GetActorLocation());

	AimingComponent->Fire(); // TODO don't fire all the time

		// AimAtPlayer();

	// UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking every s"));
}



/* Comment out
void ATankAIController::AimAtPlayer() const
{
	auto PlayerTank = GetPlayerTank();
	auto OurTank = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at player in location: %s "),*OurTank , *PlayerTank->GetActorLocation().ToString())

}
*/





