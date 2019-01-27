// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// class UTankBarrel;
// class UTankAimingComponent;
// class UTankTurret;
// class AProjectile;
// class UTankMovementComponent; Removed this as we are not really using it as part of tank.cpp



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// void AimAt(FVector HitLocation);

	

};
