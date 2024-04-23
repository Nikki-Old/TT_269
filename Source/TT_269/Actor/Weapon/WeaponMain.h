// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "WeaponMain.generated.h"

class UGameInstanceMain;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponIsInitialized);
// delegate to call in Character for Play fire Animation:
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponFireStart, UAnimMontage*, AnimFireChar);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNeededReload);


UCLASS()
class TT_269_API AWeaponMain : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponMain();

	/** Load info and set information */
	virtual void InitializeWeapon();

	/** Delegate for check is initialized */
	UPROPERTY(BlueprintAssignable, Category = "WeaponMain")
	FOnWeaponIsInitialized OnWeaponIsInitialized;

	UPROPERTY(BlueprintAssignable, Category = "WeaponMain")
	FOnWeaponFireStart OnWeaponFireStart;

	/** Call if ammo == 0 */
	UPROPERTY(BlueprintAssignable, Category = "WeaponMain")
	FOnNeededReload OnNeededReload;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponMain")
	void GetWeaponActorInfo(FWeaponActorInfo& OutInfo) const { OutInfo = WeaponActorInfo; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponMain")
	void Attack();
	void Attack_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponMain")
	void StopAttack();
	void StopAttack_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Find information by this name in Table */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "WeaponMain", meta = (ExposeOnSpawn = true))
	FName WeaponName = "";

	/** Main information for this weapon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMain")
	FWeaponActorInfo WeaponActorInfo = FWeaponActorInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot")
	UGameInstanceMain* GetGameInstanceMain() const { return GameInstanceMain; };

	static UGameInstanceMain* GameInstanceMain;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "WeaponMain | Fire")
	void StartFire();
	void StartFire_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "WeaponMain | Fire")
	void Fire();
	void Fire_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMain | Fire")
	FName MuzzleFlashSocketName = "MuzzleFlash";

	UFUNCTION(BlueprintCallable, Category = "WeaponMain")
	void SetMuzzleFlashRelativeTransform(FTransform NewTransform) { MuzzleFlashRelativeTransform = NewTransform; }

	FTransform MuzzleFlashRelativeTransform = FTransform();

private:
	UPROPERTY()
	FTimerHandle FireTimer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
