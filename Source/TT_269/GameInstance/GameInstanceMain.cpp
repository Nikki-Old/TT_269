// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstanceMain.h"

bool UGameInstanceMain::GetInventoryInfoByItemInfo(const FItemActorInfo& ItemActorInfo, FInventorySlotInfo& OutInfo)
{
	if (!ItemActorInfo.IsEmpty())
	{
		if (ItemTables.Contains(ItemActorInfo.ItemType))
		{
			// Get target table by item type:
			const auto TargetTable = ItemTables[ItemActorInfo.ItemType];

			if (TargetTable)
			{
				FInventorySlotInfo* NeededInfo = TargetTable->FindRow<FInventorySlotInfo>(ItemActorInfo.ItemName, "", false);
				if (NeededInfo)
				{
					OutInfo = *NeededInfo;
					return true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Not find item by name: %s"), ItemActorInfo.ItemName);
				}
			}
		}
	}

	return false;
}

bool UGameInstanceMain::GetAmmoInfoByName(const FName& TargetName, FAmmoActorInfo& OutInfo)
{
	// Get target table by item type:
	const auto TargetTable = ItemTables[EItemType::Ammo_Type];
	check(TargetTable);

	if (TargetTable)
	{
		FAmmoActorInfo* NeededInfo = TargetTable->FindRow<FAmmoActorInfo>(TargetName, "", false);
		if (NeededInfo)
		{
			OutInfo = *NeededInfo;
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not find item by name: %s"), TargetName);
		}
	}

	return false;
}

bool UGameInstanceMain::GetWeaponInfoByName(const FName& TargetName, FWeaponActorInfo& OutInfo)
{
	// Get target table by item type:
	const auto TargetTable = ItemTables[EItemType::Weapon_Type];

	check(TargetTable);
	if (TargetTable)
	{
		FWeaponActorInfo* NeededInfo = TargetTable->FindRow<FWeaponActorInfo>(TargetName, "", false);
		if (NeededInfo)
		{
			OutInfo = *NeededInfo;
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not find item by name: %s"), TargetName);
		}
	}


	return false;
}

bool UGameInstanceMain::GetOtherActorInfoByName(const FName& TargetName, FOtherItemActorInfo& OutInfo)
{
	const auto TargetTable = ItemTables[EItemType::Other_Type];
	check(TargetTable);

	if (TargetTable)
	{
		FOtherItemActorInfo* NeededInfo = TargetTable->FindRow<FOtherItemActorInfo>(TargetName, "", false);
		if (NeededInfo)
		{
			OutInfo = *NeededInfo;
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not find item by name: %s"), TargetName);
		}
	}

	return false;
}
