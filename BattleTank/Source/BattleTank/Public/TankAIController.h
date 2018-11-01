// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	void Tick(float DeltaTime) override;

public:
	

	void BeginPlay() override;

private: 

	ATank* GetControllerTank() const;

	ATank* GetPlayerTank() const; 

	void AimAtPlayer() const;
	
	
};
