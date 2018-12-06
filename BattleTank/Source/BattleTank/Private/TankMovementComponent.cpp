// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Math/Vector.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet; 
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	// log tank name and Value of Move Velocity
	// auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto RequiredThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RequiredRotation = FVector::CrossProduct(TankForward, AIForwardIntention);

	IntendTurnRight(RequiredRotation.Z);
	IntendMoveForward(RequiredThrow);
	
	UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), RequiredThrow, RequiredThrow)


}


