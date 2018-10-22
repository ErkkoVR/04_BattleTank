// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControllerTank() const;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:

	// Start the tank to aimtowards what we are pointing to 
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const; 
};
