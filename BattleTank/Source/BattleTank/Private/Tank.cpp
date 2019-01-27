// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
// #include "TankAimingComponent.h"
#include "Engine/World.h"
//#include "TankBarrel.h"
//#include "Projectile.h"
// #include "TankMovementComponent.h" Commented out as we are not using it in tank really. 



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ construct"), *TankName)

	// No need to add protection as as added at construction
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}







