// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstanceMain.h"

bool UGameInstanceMain::GetInventoryInfoByItemInfo(const FItemActorInfo& ItemActorInfo, FInventorySlotInfo& OutInfo)
{
	if (!ItemActorInfo.IsEmpty())
	{
		if (Tables.Contains(ItemActorInfo.ItemType))
		{
			const auto TargetTable = Tables[ItemActorInfo.ItemType];

			if (TargetTable)
			{
				FInventorySlotInfo* NeededInfo = TargetTable->FindRow<FInventorySlotInfo>(ItemActorInfo.ItemName, "", false);
				if (NeededInfo)
				{
					OutInfo = *NeededInfo;
					return true;
				}
			}
		}
	}

	return false;
}

bool UGameInstanceMain::GetWeaponInfoByName(const FName& TargetName, FWeaponActorInfo& OutInfo)
{
	const auto TargetTable = Tables[EItemType::Weapon_Type];

	if (TargetTable)
	{
		FWeaponActorInfo* NeededInfo = TargetTable->FindRow<FWeaponActorInfo>(TargetName, "", false);
		if (NeededInfo)
		{
			OutInfo = *NeededInfo;
			return true;
		}
	}

	return false;
}

bool UGameInstanceMain::GetOtherActorInfoByName(const FName& TargetName, FOtherItemActorInfo& OutInfo)
{
	const auto TargetTable = Tables[EItemType::Other_Type];

	if (TargetTable)
	{
		FOtherItemActorInfo* NeededInfo = TargetTable->FindRow<FOtherItemActorInfo>(TargetName, "", false);
		if (NeededInfo)
		{
			OutInfo = *NeededInfo;
			return true;
		}
	}

	return false;
}
