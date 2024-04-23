// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "WeaponMain.generated.h"

class UGameInstanceMain;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponIsInitialized);

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponMain")
	void GetWeaponActorInfo(FWeaponActorInfo& OutInfo) const { OutInfo = WeaponActorInfo; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Find information by this name in Table */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "WeaponMain", meta = (ExposeOnSpawn = true))
	FName WeaponName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMain")
	FWeaponActorInfo WeaponActorInfo = FWeaponActorInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot")
	UGameInstanceMain* GetGameInstanceMain() const { return GameInstanceMain; };

	static UGameInstanceMain* GameInstanceMain;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
