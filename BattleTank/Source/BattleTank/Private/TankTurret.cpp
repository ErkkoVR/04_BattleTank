// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{

	// auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f: Turret->Move called"), Time)

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPersecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	// 	auto ElevationChange = (FMath::Clamp<float>(RelativeSpeed, -1, +1)) * MaxDegreesPersecond * GetWorld()->DeltaTimeSeconds;
	// auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}


