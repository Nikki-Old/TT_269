// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/** For broadcast Current Health and Change: */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChangeHealth, AActor*, Owner, float, CurrentHealth, float, Change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChangeMaxHealth, AActor*, Owner, float, OldMaxHealth, float, NewMaxHealth);

/** Broadcast On Dead: */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDead, AActor*, Owner, AActor*, LastDamageCauser);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HPPLUGIN_API UHealthComponent : public UActorComponent
{

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	// Delegates:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnChangeHealth OnChangeHealth;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnChangeMaxHealth OnChangeMaxHealth;

	/** For Owner, can bind this broadcast and Owner custom function: */
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDead OnDead;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void RestoreHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float NewMaxHealh);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	int MaxHealth = 100.0f;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	AActor* GetLastDamageCauser() const { return LastDamageCauser; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	bool bIsNeedMaxHealth = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Initial Function: */
	virtual void InititalHealthComponent();

	/** Healh: */
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Health")
	float Health = MaxHealth;

	/**Is Dead*/
	bool bIsDead = false;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///* Particles on Damage : */
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX")
	// TArray<TSoftObjectPtr<UParticleSystem>> DamageParticles;

	///* Decals after DamageParticle :*/
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX")
	// UMaterial* DamageDecalMaterial = nullptr;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX")
	// float LifeDamageDecal = 1.0f;

	///* Decals on walss after take damage */
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX | Walls")
	// TArray<TSoftObjectPtr<UMaterialInstance>> DecalOnWallsMaterial;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX | Walls")
	// float MaxDistanceToSpawnDecalOnWalls = 300.0f;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | FX | Walls")
	// float LifeDecalOnWalls = 2.0f;

	///** If Need Spawn Damage widget, set TRUE: */
	// UPROPERTY(EditDefaultsOnly, Category = "Health | Damage")
	// bool bIsNeedSpawnDamage = false;

	/** Offset spawn location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health | Damage", meta = (EditCondition = "bIsNeedSpawnDamage"))
	FVector DamageOffsetLocation = FVector(0);

	/** Current Damage * DamageCoef = Change Health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health | Damage")
	float DamageCoef = 1.0f;

	///** Class Damage Actor: */
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health | Damage", meta = (EditCondition = "bIsNeedSpawnDamage"))
	// TSubclassOf<class ADamageBase> HealthDamageClass;

	// Healts:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void ChangeHealth(const float Change, AActor* Causer);

	// Dead:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool IsDead() const { return bIsDead; }

	// State Effect:

protected:
	// void SpawnDamageActor(TSubclassOf<class ADamageBase> DamageClass, const float Change);

	// bool bIsSpawnDamageParticle = false;

	/** Bind this function and Owner Delegate - "OnTakeAnyDamage". */
	UFUNCTION()
	virtual void OwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/** Bind this function and Owner Delegate - "OnTakePointDamage". */
	UFUNCTION()
	virtual void OwnerTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	/** Bind this function and Owner Delegate - "OnTakeRadialDamage". */
	UFUNCTION()
	virtual void OwnerTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	/*
	UFUNCTION()
	void SpawnEmitterPointDamage(FVector SpawnLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HealthComponent")
	void SpawnEmitterDecals(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);
	void SpawnEmitterDecals_Implementation(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);
	*/

	/*void TrySpawnDecalOnWalls(FVector HitLocation, FVector CauserLocation);*/

public:
	// State Effect Intreface:

	///** Check: Return can set state effect for this Actor: */
	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateEffect")
	// bool IsCanSetStateEffect();
	// bool IsCanSetStateEffect_Implementation();

	///** Get Current State Effects: */
	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateEffect")
	// TArray<UStateEffect*> GetStateEffects() const;
	// TArray<UStateEffect*> GetStateEffects_Implementation() const;

	///** Add State Effect: */
	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateEffect")
	// bool AddStateEffect(UStateEffect* NewStateEffect);
	// bool AddStateEffect_Implementation(UStateEffect* NewStateEffect);

	///** Remove State Effect: */
	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateEffect")
	// bool RemoveStateEffect(UStateEffect* StateEffect);
	// bool RemoveStateEffect_Implementation(UStateEffect* StateEffect);

	//// State Effect End
private:
	/** Damage Hit Location */
	UPROPERTY()
	FVector DamageHitLocation = FVector(0);

	UPROPERTY()
	AActor* LastDamageCauser = nullptr;
};
