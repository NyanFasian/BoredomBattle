// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{

	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *(GetOwner()->GetName()),	*(AimLocation.ToString()), *(Barrel->GetComponentLocation().ToString()))
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("Barrel hasn't been assigned"))
		return;
	}
	FVector OUTTossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringSocket"));
	
	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OUTTossVelocity,
			StartLocation,
			AimLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace

		)) {
		FVector AimDirection = OUTTossVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming direction: %s"), *(AimDirection.ToString()))

		MoveBarrel(AimDirection);
	}

	

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Work out differences between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}

