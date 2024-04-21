// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/Inventory/WeaponInventoryComponent.h"

UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	WeaponsInfo.Add(TTuple<EWeaponSlotType, FInventorySlotInfo>(EWeaponSlotType::First_Type, FInventorySlotInfo()));
	WeaponsInfo.Add(TTuple<EWeaponSlotType, FInventorySlotInfo>(EWeaponSlotType::Second_Type, FInventorySlotInfo()));
}

bool UWeaponInventoryComponent::AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity)
{
	if (!NewItemInfo.IsEmpty())
	{

	}
	else
	{
		return false;
	}

	return Super::AddItemInfo(NewItemInfo, Quantity);
}
