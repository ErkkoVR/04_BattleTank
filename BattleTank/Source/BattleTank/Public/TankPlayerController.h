// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// #include "Tank.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControllerTank() const;

public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.215;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000000;

	// Start the tank to aimtowards what we are pointing to 
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& StartLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector StartLocation, FVector& HitLocation) const;	

	


		
};
