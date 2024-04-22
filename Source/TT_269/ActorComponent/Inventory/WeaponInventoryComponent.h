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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API UWeaponInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	UWeaponInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "WeaponInventory")
	FOnUpdateWeaponSlot OnUpdateWeaponSlot;

	virtual bool AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponInventory")
	void GetWeaponsInfo(TMap<EWeaponSlotType, FWeaponActorInfo>& OutInfo) { OutInfo = WeaponsInfo; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeaponInventory")
	bool IsHaveFreeSlot(EWeaponSlotType TargetType, FWeaponActorInfo& TargetInfo) const;

private:
	UPROPERTY()
	TMap<EWeaponSlotType, FWeaponActorInfo> WeaponsInfo = {};
};
