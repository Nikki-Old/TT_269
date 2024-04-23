// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMain.h"
#include "FunctionLibrary/FrameworkLibrary.h"

#include "GameInstance/GameInstanceMain.h"
#include "Actor/Projectile/WeaponProjectileMain.h"

UGameInstanceMain* AWeaponMain::GameInstanceMain = nullptr;

// Sets default values
AWeaponMain::AWeaponMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponMain::Attack_Implementation()
{
	if (WeaponActorInfo.CurrentAmmo > 0)
	{
		// Is auto fire?
		if (WeaponActorInfo.WeaponDamageInfo.bIsAutoFire)
		{
			StartFire();
		}
		else
		{
			Fire();
		}
	}
	else
	{
		OnNeededReload.Broadcast();
	}
}

void AWeaponMain::StopAttack_Implementation()
{
	if (FireTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}

// Called when the game starts or when spawned
void AWeaponMain::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstanceMain)
	{
		GameInstanceMain = UFrameworkLibrary::GetGameInstanceMain(GetWorld());
	}

	InitializeWeapon();
}

void AWeaponMain::InitializeWeapon()
{
	if (GameInstanceMain)
	{
		if (GameInstanceMain->GetWeaponInfoByName(WeaponName, WeaponActorInfo))
		{
			OnWeaponIsInitialized.Broadcast();
		}
	}
}

// Called every frame
void AWeaponMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		GameInstanceMain = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void AWeaponMain::StartFire_Implementation()
{
	if (!FireTimer.IsValid())
	{
		// Set timer how can often fire.
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AWeaponMain::Fire, WeaponActorInfo.WeaponDamageInfo.RateOfFire, true);
	}
}

void AWeaponMain::Fire_Implementation()
{
	// If not have Owner - return;
	if (!GetOwner())
		return;

	if (IsValid(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo.Class))
	{
		OnWeaponFireStart.Broadcast(WeaponActorInfo.CharacterAnimation.AttackAnimMontage);

		//// FX start:
		///*Set sound Weapon.*/
		// if (WeaponSetting.SoundFireWeapon)
		//	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponSetting.SoundFireWeapon, ShootLocation->GetComponentLocation());

		FTransform SpawnTransform = MuzzleFlashRelativeTransform;
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + this->GetActorLocation());
		SpawnTransform.SetRotation(FQuat(SpawnTransform.GetRotation().Rotator() + this->GetActorRotation()));

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AWeaponProjectileMain* Projectile = GetWorld()->SpawnActorDeferred<AWeaponProjectileMain>(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo.Class, SpawnTransform, this);
		if (Projectile)
		{
			Projectile->InitProjectile(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo);
			Projectile->SetInstigator(GetInstigator());
			Projectile->FinishSpawning(SpawnTransform);
		}
	}
}
