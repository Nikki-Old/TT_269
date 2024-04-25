// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretMain.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Actor/Projectile/WeaponProjectileMain.h"

ATurretMain::ATurretMain()
{
	// Create base mesh:
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetMesh());

	// Create turn yaw mesh:
	TurnYawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnYawMesh"));
	TurnYawMesh->SetupAttachment(BaseMesh);

	// Create turn pitch mesh:
	TurnPitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnPitchMesh"));
	TurnPitchMesh->SetupAttachment(TurnYawMesh);

	// Create shoot direction arrow component:
	ShootDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootDirection"));
	ShootDirection->SetupAttachment(TurnPitchMesh);
}

void ATurretMain::StartShootAtLocation(FVector TargetLocation)
{
	if (GetWorld())
	{
		TargetRotate = UKismetMathLibrary::FindLookAtRotation(BaseMesh->GetComponentLocation(), TargetLocation);

		if (bIsCanRotate)
		{
			if (!UpdateRotateTimer.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(UpdateRotateTimer, this, &ATurretMain::UpdateLookAtRotation, TurretInfo.HowOftenUpdateRotation, true);
			}
		}
	}
}

void ATurretMain::StartShootToTarget(AActor* NewTarget)
{
	ShootTarget = NewTarget;

	if (ShootTarget)
	{
		StartShootAtLocation(ShootTarget->GetActorLocation());
	}
}

void ATurretMain::SetCanRotate(bool bIsCan)
{
	bIsCanRotate = bIsCan;
	if (bIsCanRotate)
	{
		// TO DO: start rate to target
	}
	else
	{
		if (UpdateRotateTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(UpdateRotateTimer);
		}
	}
}

bool ATurretMain::IsTurnToTarget() const
{
	auto CurrentPitchMeshRotation = TurnPitchMesh->GetComponentRotation();
	auto TargetPitchMeshRotation = CurrentPitchMeshRotation;
	TargetPitchMeshRotation.Pitch = TargetRotate.Pitch;

	if (!CurrentPitchMeshRotation.Equals(TargetPitchMeshRotation, 0.1f))
	{
		return false;
	}

	auto CurrentYawMeshRotation = TurnYawMesh->GetComponentRotation();
	auto TargetYawMeshRotation = CurrentYawMeshRotation;
	TargetYawMeshRotation.Yaw = TargetRotate.Yaw;

	if (!CurrentYawMeshRotation.Equals(TargetYawMeshRotation, 0.1f))
	{
		return false;
	}

	return true;
}

void ATurretMain::UpdateLookAtRotation()
{
	bool bIsCanFire = true;

	auto CurrentPitchMeshRotation = TurnPitchMesh->GetComponentRotation();
	auto TargetPitchMeshRotation = CurrentPitchMeshRotation;
	TargetPitchMeshRotation.Pitch = TargetRotate.Pitch;

	if (!CurrentPitchMeshRotation.Equals(TargetPitchMeshRotation, 0.01f))
	{
		TurnPitchMesh->SetWorldRotation(FMath::RInterpTo(CurrentPitchMeshRotation, TargetPitchMeshRotation, TurretInfo.HowOftenUpdateRotation, TurretInfo.UpdateRotateSpeed));
		bIsCanFire = false;
	}

	auto CurrentYawMeshRotation = TurnYawMesh->GetComponentRotation();
	auto TargetYawMeshRotation = CurrentYawMeshRotation;
	TargetYawMeshRotation.Yaw = TargetRotate.Yaw;

	if (!CurrentYawMeshRotation.Equals(TargetYawMeshRotation, 0.01f))
	{
		TurnYawMesh->SetWorldRotation(FMath::RInterpTo(CurrentYawMeshRotation, TargetYawMeshRotation, TurretInfo.HowOftenUpdateRotation, TurretInfo.UpdateRotateSpeed));
		bIsCanFire = false;
	}

	if (bIsCanFire)
	{
		SetCanRotate(false);
		Fire();
	}
}

void ATurretMain::Fire_Implementation()
{
	if (GetWorld())
	{
		// Spawn projectile:
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FTransform SpawnTransform = ShootDirection->GetComponentTransform();

		AWeaponProjectileMain* Projectile = GetWorld()->SpawnActorDeferred<AWeaponProjectileMain>(TurretInfo.ProjectileInfo.Class, SpawnTransform, this);
		if (Projectile)
		{
			Projectile->InitProjectile(TurretInfo.ProjectileInfo);
			Projectile->SetInstigator(GetInstigator());
			Projectile->FinishSpawning(SpawnTransform);
		}
		
		// TO DO: Add sound and FX

		if (IsTurnToTarget())
		{
			// Start deleay fire:
			GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &ATurretMain::Fire, TurretInfo.FireRate, false);
		}
		else
		{
			SetCanRotate(true);
		}

		if (ShootTarget)
		{
			StartShootAtLocation(ShootTarget->GetActorLocation());
		}
	}
}
