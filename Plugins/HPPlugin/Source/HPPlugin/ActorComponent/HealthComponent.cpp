// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::RestoreHealth()
{
	bIsDead = false;
	SetCurrentHealth(GetMaxHealth());
}

void UHealthComponent::SetCurrentHealth(float NewValue)
{
	ChangeHealth(NewValue - Health, nullptr);
}

void UHealthComponent::SetMaxHealth(float NewMaxHealh)
{
	const auto Temp = MaxHealth;
	MaxHealth = NewMaxHealh;

	OnChangeMaxHealth.Broadcast(GetOwner(), Temp, MaxHealth);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	InititalHealthComponent();
}

void UHealthComponent::InititalHealthComponent()
{
	// Bind to Owner "TakeAnyDamage"
	if (!GetOwner())
		return;

	// Bind Owner "OnTakeAnyDamage" and "OwnerTakeAnyDamage" function:
	auto OwnerActor = Cast<AActor>(GetOwner());
	if (OwnerActor)
	{
		OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OwnerTakeAnyDamage);
		OwnerActor->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OwnerTakePointDamage);
		OwnerActor->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::OwnerTakeRadialDamage);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ChangeHealth(const float Change, AActor* Causer)
{
	if (bIsDead || Change == 0.f)
		return;

	// Change Health:
	if (bIsNeedMaxHealth)
	{
		Health = FMath::Clamp(Health + Change, 0.0f, (float)MaxHealth);
	}
	else
	{
		Health = FMath::Clamp(Health + Change, 0.0f, FLT_MAX);
	}

	if (Change < 0)
	{
		// if (bIsNeedSpawnDamage)
		//{
		//	SpawnDamageActor(HealthDamageClass, Change);
		//	OnTakeDamage.Broadcast(Change);
		// }

		LastDamageCauser = Causer;
	}

	if (Health > MaxHealth && bIsNeedMaxHealth)
	{
		Health = MaxHealth;
	}

	if (Health <= 0)
	{
		// if (LastDamageCauser)
		//{
		//	if (LastDamageCauser->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass()))
		//	{
		//		ICharacterInterface::Execute_CharacterIsKill(LastDamageCauser, GetOwner());
		//	}
		// }

		bIsDead = true;
		OnDead.Broadcast(GetOwner(), LastDamageCauser);
	}

	OnChangeHealth.Broadcast(GetOwner(), Health, Change);
}

void UHealthComponent::OwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!bIsDead)
	{
		Damage *= DamageCoef;
		ChangeHealth(-Damage, DamageCauser);
	}
}

void UHealthComponent::OwnerTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (FMath::IsNearlyZero(Damage) && !DamageCauser)
	{
		return;
	}

	DamageHitLocation = HitLocation;

	// TrySpawnDecalOnWalls(HitLocation, DamageCauser->GetActorLocation());
}

void UHealthComponent::OwnerTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	if (FMath::IsNearlyZero(Damage) && !DamageCauser)
	{
		return;
	}

	DamageHitLocation = HitInfo.Location;

	// TrySpawnDecalOnWalls(HitInfo.Location, DamageCauser->GetActorLocation());
}

/*
void UHealthComponent::SpawnEmitterPointDamage(FVector SpawnLocation)
{
	if (!GetWorld() && !GetOwner())
		return;

	// Take random index:
	int Index = FMath::RandHelper(DamageParticles.Num() - 1);

	// Check: Index is Valid?...
	if (DamageParticles.IsValidIndex(Index))
	{
		// Load Particle...
		UParticleSystem* ParticleSystem = Cast<UParticleSystem>(UKismetSystemLibrary::LoadAsset_Blocking(DamageParticles[Index]));

		if (ParticleSystem)
		{
			// Spawn Emitter:
			auto SpawnEmitter = UGameplayStatics::SpawnEmitterAttached(ParticleSystem, GetOwner()->GetRootComponent(), FName(), SpawnLocation, FRotator(), EAttachLocation::KeepWorldPosition);
			SpawnEmitter->OnParticleCollide.AddDynamic(this, &UHealthComponent::SpawnEmitterDecals);
		}
	}
}

void UHealthComponent::SpawnEmitterDecals_Implementation(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat)
{
}*/

// void UHealthComponent::TrySpawnDecalOnWalls(FVector HitLocation, FVector CauserLocation)
//{
//	if (!GetOwner() && !GetWorld())
//		return;
//
//	FVector Result = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(CauserLocation, HitLocation)) * MaxDistanceToSpawnDecalOnWalls;
//
//	FHitResult ResultHit;
//
//	FCollisionQueryParams CollisionQueryParams;
//	CollisionQueryParams.AddIgnoredActor(GetOwner());
//
//	// UKismetSystemLibrary::DrawDebugLine(GetWorld(), HitLocation, Result, FLinearColor::Red, 10.f);
//	GetWorld()->LineTraceSingleByChannel(ResultHit, HitLocation, HitLocation + Result, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
//
//	if (!ResultHit.bBlockingHit)
//		return;
//
//	// Choose Material for Decal:
//	int8 Index = FMath::RandHelper(DecalOnWallsMaterial.Num() - 1);
//
//	if (DecalOnWallsMaterial.IsValidIndex(Index))
//	{
//		UMaterialInstance* DecalMaterial = Cast<UMaterialInstance>(UKismetSystemLibrary::LoadAsset_Blocking(DecalOnWallsMaterial[Index]));
//
//		// check(DecalMaterial);
//
//		if (DecalMaterial)
//		{
//			auto Rotation = UKismetMathLibrary::MakeRotFromX(ResultHit.Normal);
//			// Spawn Decal
//			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(50.0f, 50.0f, 50.f), ResultHit.Location, Rotation, LifeDecalOnWalls);
//		}
//	}
// }

// bool UHealthComponent::IsCanSetStateEffect_Implementation()
//{
//	return bIsCanSetState;
// }
//
// TArray<UStateEffect*> UHealthComponent::GetStateEffects_Implementation() const
//{
//	return StateEffects;
// }
//
// bool UHealthComponent::AddStateEffect_Implementation(UStateEffect* NewStateEffect)
//{
//	if (!NewStateEffect)
//		return false;
//
//	// If not is Statckable:
//	if (!NewStateEffect->bIsStackable)
//	{
//		// Check: not have same class:
//		if (!UTPSSimpleThingsLibrary::FindSameStateClass(NewStateEffect, StateEffects))
//		{
//			StateEffects.Add(NewStateEffect);
//			return true;
//		}
//	}
//	else
//	{
//		StateEffects.Add(NewStateEffect);
//		return true;
//	}
//
//	return false;
// }
//
// bool UHealthComponent::RemoveStateEffect_Implementation(UStateEffect* StateEffect)
//{
//	if (!StateEffect)
//		return false;
//
//	for (auto State : StateEffects)
//	{
//		if (State == StateEffect)
//		{
//			StateEffects.Remove(State);
//			return true;
//		}
//	}
//
//	return false;
// }

// void UHealthComponent::SpawnDamageActor(TSubclassOf<ADamageBase> DamageClass, const float Change)
//{
//	if (!GetWorld() && !IsValid(DamageClass))
//		return; // TO DO Check();
//
//	auto SpawnTransform = this->GetOwner()->GetTransform();
//
//	auto DamageActor = (GetWorld()->SpawnActor<ADamageBase>(DamageClass, SpawnTransform));
//
//	if (DamageActor)
//	{
//		// Add offset:
//		auto OldLocation = this->GetOwner()->GetActorLocation();
//		FVector LocationWithOffset = FVector(0);
//
//		if (!DamageHitLocation.IsNearlyZero())
//		{
//			LocationWithOffset += (OldLocation - DamageHitLocation);
//		}
//		DamageActor->SetActorLocation(OldLocation + DamageOffsetLocation + LocationWithOffset);
//
//		DamageActor->UpdateDamageWidget(GetHealth(), Change);
//	}
//
//	DamageHitLocation = FVector(0);
// }
