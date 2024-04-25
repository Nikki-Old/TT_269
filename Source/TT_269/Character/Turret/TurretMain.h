// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "TurretMain.generated.h"

class UArrowComponent;
class AWeaponProjectileMain;

/**
 *
 */

USTRUCT(BlueprintType)
struct FTurretInfo
{
	GENERATED_BODY()

	/** How often call "UpdateLookAtRotation" **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurretInfo", meta = (ClampMin = 0.001f, UIMin = 0.001f))
	float HowOftenUpdateRotation = 0.001f;

	/** Step rotate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurretInfo", meta = (ClampMin = 0.001f, UIMin = 0.001f))
	float UpdateRotateSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurretInfo", meta = (ClampMin = 0.001f, UIMin = 0.001f))
	float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurretInfo")
	FProjectileInfo ProjectileInfo = FProjectileInfo();
};

UCLASS()
class TT_269_API ATurretMain : public ACharacter
{
	GENERATED_BODY()

public:
	ATurretMain();

	/** Base of turret */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "TurretMain")
	UStaticMeshComponent* BaseMesh = nullptr;

	/** Turn yaw mesh of turret */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "TurretMain")
	UStaticMeshComponent* TurnYawMesh = nullptr;

	/** Turn pitch mesh of turret */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "TurretMain")
	UStaticMeshComponent* TurnPitchMesh = nullptr;

	/** Shoot direction */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "TurretMain")
	UArrowComponent* ShootDirection = nullptr;

	/** Start rotate to location and 
	if current shoot direction == target location - shoot. */
	UFUNCTION(BlueprintCallable, Category = "TurretMain")
	void StartShootAtLocation(FVector TargetLocation);

	/** Set can rotate */
	UFUNCTION(BlueprintCallable, Category = "TurretMain")
	void SetCanRotate(bool bIsCan);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TurretMain")
	bool IsTurnToTarget() const;

protected:
	UFUNCTION()
	void UpdateLookAtRotation();

	UFUNCTION(BlueprintNativeEvent, Category = "TurrentMain")
	void Fire();
	void Fire_Implementation();

	/** Main information */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurretMain")
	FTurretInfo TurretInfo;

private:
	FVector TargetShootLocation = FVector(0);
	FRotator TargetRotate = FRotator(0);

	FTimerHandle UpdateRotateTimer;
	FTimerHandle FireRateTimer;

	/** Flag can rotate */
	bool bIsCanRotate = true;
};
