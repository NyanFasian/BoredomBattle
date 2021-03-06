// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BOREDOMBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegrees = 0.0f;
	
};
