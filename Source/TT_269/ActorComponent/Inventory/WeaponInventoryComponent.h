// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/Inventory/InventoryComponent.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "WeaponInventoryComponent.generated.h"

/**
 * 
 */

UCLASS()
class TT_269_API UWeaponInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()
	
public:
	UWeaponInventoryComponent();

	virtual bool AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity) override;

	TMap<EWeaponSlotType, FInventorySlotInfo> WeaponsInfo = {};
};
