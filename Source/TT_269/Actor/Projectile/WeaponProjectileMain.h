// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "WeaponProjectileMain.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TT_269_API AWeaponProjectileMain : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponProjectileMain();

	// Components:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USphereComponent* Collision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	/** Set Base Parameters: */
	void InitProjectile(FProjectileInfo InitParam);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Hit Event:
	UFUNCTION()
	virtual void CollisionHit(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	// BeginOverlap Event:
	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// EndOverlap Event:
	UFUNCTION()
	void CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void ImpactProjectile();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FProjectileInfo ProjectileInfo = FProjectileInfo();
};
