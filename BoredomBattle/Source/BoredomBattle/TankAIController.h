// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOREDOMBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 3000;

private:
	virtual void SetPawn(APawn* InPawn)override;

	UFUNCTION()
	void OnPossessedTankDeath();
	
};
