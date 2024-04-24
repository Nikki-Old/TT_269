// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMain.h"
#include "FunctionLibrary/FrameworkLibrary.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameInstance/GameInstanceMain.h"
#include "Actor/Projectile/WeaponProjectileMain.h"

UGameInstanceMain* AWeaponMain::GameInstanceMain = nullptr;

// Sets default values
AWeaponMain::AWeaponMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create "root":
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	this->SetRootComponent(SceneComponent);

	// Create skeletal mesh for weapon:
	WeaponSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSK"));
	WeaponSK->SetupAttachment(GetRootComponent());
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

void AWeaponMain::AddAmmoQuantity(const int32 NewQuantity)
{
	OnChangeAmmo.Broadcast(WeaponActorInfo.CurrentAmmo += NewQuantity);
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
	//// Set muzzle offset:
	// MuzzleFlashOffset = WeaponSK->GetSocketTransform(MuzzleFlashSocketName, ERelativeTransformSpace::RTS_ParentBoneSpace);

	if (WeaponActorInfo.IsEmpty())
	{
		if (GameInstanceMain)
		{
			if (GameInstanceMain->GetWeaponInfoByName(WeaponName, WeaponActorInfo))
			{
				OnWeaponIsInitialized.Broadcast();
			}
		}
	}
	else
	{
		OnWeaponIsInitialized.Broadcast();
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
		// First shoot:
		Fire();

		// Set timer how can often fire.
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AWeaponMain::Fire, WeaponActorInfo.WeaponDamageInfo.RateOfFire, true);
	}
}

void AWeaponMain::Fire_Implementation()
{
	// If not have Owner - return;
	if (!GetOwner())
		return;

	if (WeaponActorInfo.CurrentAmmo > 0)
	{
		if (IsValid(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo.Class))
		{
			OnChangeAmmo.Broadcast(--WeaponActorInfo.CurrentAmmo);
			OnWeaponFireStart.Broadcast(WeaponActorInfo.CharacterAnimation.AttackAnimMontage);

			//// FX start:
			///*Set sound Weapon.*/
			// if (WeaponSetting.SoundFireWeapon)
			//	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponSetting.SoundFireWeapon, ShootLocation->GetComponentLocation());

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			FTransform SpawnTransform = WeaponSK->GetSocketTransform(MuzzleFlashSocketName);
			/*SpawnTransform.SetLocation();
			SpawnTransform.SetRotation(FMatrix(WeaponSK->GetForwardVector(), FVector(0, 1, 0), FVector(0, 0, 1), FVector::ZeroVector).ToQuat());*/

			AWeaponProjectileMain* Projectile = GetWorld()->SpawnActorDeferred<AWeaponProjectileMain>(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo.Class, SpawnTransform, this);
			if (Projectile)
			{
				Projectile->InitProjectile(WeaponActorInfo.WeaponDamageInfo.ProjectileInfo);
				Projectile->SetInstigator(GetInstigator());
				Projectile->FinishSpawning(SpawnTransform);
			}
		}
	}
	else
	{
		AWeaponMain::StopAttack();
	}
}
