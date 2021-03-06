// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming states
UENUM()
enum class EAimingStatus : uint8 {
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

// FORWARD DECLARATION EXAMPLE!!!
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOREDOMBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingStatus AimingStatus = EAimingStatus::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	EAimingStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAmmo() const;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0f;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 MaxAmmo = 3;

	int32 CurrentAmmo;

	float LastFireTime = 0;
	FVector AimDirection;

	void MoveBarrel(FVector AimDirection);
	bool IsBarrelMoving();

};
