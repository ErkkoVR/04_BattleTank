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

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.215;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000000;

	// Start the tank to aimtowards what we are pointing to 
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& StartLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector StartLocation, FVector& HitLocation) const;	

	


		
};
