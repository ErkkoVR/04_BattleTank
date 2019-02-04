// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit"))
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{

	// Super::TickComponent();
	// UE_LOG(LogTemp, Warning, TEXT("Track ticking"));
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// calculate slippage speed
	// work out the required accleration to correct in frame
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
 	// calculate and apply side ways force (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
	TankRoot->AddForce(CorrectionAcceleration);
}


void UTankTrack::SetThrottle(float Throttle)
{
	// auto Time = GetWorld()->GetTimeSeconds();
	// auto Name = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle)

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



