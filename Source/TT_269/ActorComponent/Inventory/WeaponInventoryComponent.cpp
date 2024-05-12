// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponent/Inventory/WeaponInventoryComponent.h"
#include "GameInstance/GameInstanceMain.h"

UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	WeaponsInfo.Add(TTuple<EWeaponSlotType, FWeaponActorInfo>(EWeaponSlotType::First_Type, FWeaponActorInfo()));
	WeaponsInfo.Add(TTuple<EWeaponSlotType, FWeaponActorInfo>(EWeaponSlotType::Second_Type, FWeaponActorInfo()));
}

bool UWeaponInventoryComponent::AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity)
{
	if (!NewItemInfo.IsEmpty())
	{
		if (NewItemInfo.ItemType == EItemType::Weapon_Type)
		{
			FWeaponActorInfo NewWeaponInfo;

			if (GetGameInstanceMain()->GetWeaponInfoByName(NewItemInfo.ItemName, NewWeaponInfo))
			{
				NewWeaponInfo.CurrentAmmo = Quantity;

				FWeaponActorInfo CurrentWeaponInfo;
				bool bIsFree = IsHaveFreeSlot(NewWeaponInfo.WeaponSlotType, CurrentWeaponInfo);

				WeaponsInfo[NewWeaponInfo.WeaponSlotType] = NewWeaponInfo;
				OnUpdateWeaponSlot.Broadcast(NewWeaponInfo.WeaponSlotType, NewWeaponInfo);

				if (!bIsFree)
				{
					// TO DO: logic for drop weapon:
				}

				if (CurrentWeaponInfoSlot == EWeaponSlotType::None_Type)
				{
					FWeaponActorInfo WeaponInfo;
					SetCurrentWeaponInfoBySlotType(NewWeaponInfo.WeaponSlotType, WeaponInfo);
				}

				return true;
			}
		}
	}
	else
	{
		return false;
	}

	return Super::AddItemInfo(NewItemInfo, Quantity);
}

bool UWeaponInventoryComponent::IsHaveFreeSlot(EWeaponSlotType TargetType, FWeaponActorInfo& TargetInfo) const
{
	if (WeaponsInfo.Contains(TargetType))
	{
		if (WeaponsInfo[TargetType].IsEmpty())
		{
			return true;
		}
		else
		{
			TargetInfo = WeaponsInfo[TargetType];
		}
	}

	return false;
}

bool UWeaponInventoryComponent::SetCurrentWeaponInfoBySlotType(EWeaponSlotType TargetSlotType, FWeaponActorInfo& CurrentWeaponInfo)
{
	if (CurrentWeaponInfoSlot != TargetSlotType)
	{
		if (WeaponsInfo.Contains(TargetSlotType) && !WeaponsInfo[TargetSlotType].IsEmpty()) 
		{
			CurrentWeaponInfoSlot = TargetSlotType;

			CurrentWeaponInfo = WeaponsInfo[TargetSlotType];

			OnUpdateCurrentWeaponSlot.Broadcast(TargetSlotType, CurrentWeaponInfo);

			return true;
		}
	}

	return false;
}

void UWeaponInventoryComponent::LoadWeaponsInfo(const TMap<EWeaponSlotType, FWeaponActorInfo>& NewWeaponsInfo)
{
	WeaponsInfo[EWeaponSlotType::First_Type] = NewWeaponsInfo[EWeaponSlotType::First_Type];
	WeaponsInfo[EWeaponSlotType::Second_Type] = NewWeaponsInfo[EWeaponSlotType::Second_Type];
	OnLoadWeaponInfo.Broadcast();
}

void UWeaponInventoryComponent::UpdateCurrentWeaponAmmoQuantity(int32 NewAmmoQuantity)
{
	WeaponsInfo[CurrentWeaponInfoSlot].CurrentAmmo = NewAmmoQuantity;
}

bool UWeaponInventoryComponent::LoadSaveBinaryData_Implementation(const TArray<uint8>& NewBinaryData)
{
	Super::LoadSaveBinaryData_Implementation(NewBinaryData);

	OnLoadWeaponInfo.Broadcast();

	return false;
}
