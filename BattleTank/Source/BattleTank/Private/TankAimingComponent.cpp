// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// RegisterComponent();
	// bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // Should this really tick? 
	PrimaryComponentTick.bStartWithTickEnabled = true;


	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();

}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming comp ticking"));
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{ 
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;

	}

}



void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from barrel at location: %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation)

	if (!ensure(Barrel && ProjectileBluePrint)) { return; }


	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		))
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: aim solution found"), Time)
	}
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: no aim solution found"), Time)

	}
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		// UE_LOG(LogTemp, Warning, TEXT("tank %s Aiming at: %s"), *TankName, *AimDirection.ToString())
		MoveBarrelTowards(AimDirection);
	}

}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	if (!ensure(Barrel) || !ensure(Turret)) {  return; }
	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())

	// always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);

	}
	// find turret socket
		// for turret socket move accoriding to aim roll
	// find barrel socket
		// for barrel move according to aim x


}

bool UTankAimingComponent::IsBarrelMoving()
{
	// get the forward vector
	// get the aimdirection
	// call the comparison
	if (!ensure(Barrel)) { return false; }

	auto BarrelRotator = Barrel->GetForwardVector();
	auto Tolerance = 0.01;
	return !(AimDirection.Equals(BarrelRotator, Tolerance));
}

// function for firing the projectile when input pressed
void UTankAimingComponent::Fire()
{
	

	if (FiringState != EFiringState::Reloading)
	{

		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBluePrint)) { return; }
		// spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	}


}
