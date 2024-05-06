// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/Inventory/InventoryComponent.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "WeaponInventoryComponent.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateWeaponSlot, EWeaponSlotType, SlotType, FWeaponActorInfo, WeaponActorInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateCurrentWeaponSlot, EWeaponSlotType, SlotType, FWeaponActorInfo, WeaponActorInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadWeaponInfo);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API UWeaponInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	UWeaponInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "WeaponInventory")
	FOnUpdateWeaponSlot OnUpdateWeaponSlot;

	UPROPERTY(BlueprintAssignable, Category = "WeaponInventory")
	FOnUpdateCurrentWeaponSlot OnUpdateCurrentWeaponSlot;

	UPROPERTY(BlueprintAssignable, Category = "WeaponInventory")
	FOnLoadWeaponInfo OnLoadWeaponInfo;

	virtual bool AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponInventory")
	void GetWeaponsInfo(TMap<EWeaponSlotType, FWeaponActorInfo>& OutInfo) { OutInfo = WeaponsInfo; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponInventory")
	bool IsHaveFreeSlot(EWeaponSlotType TargetType, FWeaponActorInfo& TargetInfo) const;

	UFUNCTION(BlueprintCallable, Category = "WeaponInventory")
	bool SetCurrentWeaponInfoBySlotType(EWeaponSlotType TargetSlotType, FWeaponActorInfo& CurrentWeaponInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponInventory")
	void GetCurrentWeaponInfoSlot(EWeaponSlotType& OutInfo) const { OutInfo = CurrentWeaponInfoSlot; }

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadWeaponsInfo(const TMap<EWeaponSlotType, FWeaponActorInfo>& NewWeaponsInfo);

	UFUNCTION(BlueprintCallable, Category = "WeaponInventory")
	void UpdateCurrentWeaponAmmoQuantity(int32 NewAmmoQuantity);

private:
	UPROPERTY()
	TMap<EWeaponSlotType, FWeaponActorInfo> WeaponsInfo = {};

	EWeaponSlotType CurrentWeaponInfoSlot = EWeaponSlotType::None_Type;
};
