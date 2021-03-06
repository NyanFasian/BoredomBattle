// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CurrentIntegrity = MaxIntegrity;	// WARNING: Too early! put it in BeginPlay

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentIntegrity = MaxIntegrity;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentIntegrity);

	CurrentIntegrity -= DamageToApply;

	if (CurrentIntegrity <= 0) {
		
		OnDeath.Broadcast();
	}

	

	return DamageToApply;
}

float ATank::GetIntegrityPercentage() const
{
	return (float)CurrentIntegrity/(float)MaxIntegrity;
}
