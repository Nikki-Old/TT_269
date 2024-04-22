// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "TT_269_Types.generated.h"

class AWeaponMain;

/**
 *
 */

// Item type:
UENUM(BlueprintType)
enum class EItemType : uint8
{
	None_Type UMETA(DisplayName = "None"),
	Ammo_Type UMETA(DisplayName = "Ammo"),
	Weapon_Type UMETA(DisplayName = "Weapon"),
	Other_Type UMETA(DisplayName = "Other"),
	MAX_Type UMETA(DisplayName = "MAX")
};

USTRUCT(BlueprintType)
struct FItemActorInfo : public FTableRowBase
{
	GENERATED_BODY()

	/** Item type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType ItemType = EItemType::None_Type;

	/** Item name == RowName */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName ItemName = "";

	virtual bool IsEmpty() const
	{
		if (ItemType == EItemType::None_Type)
		{
			return true;
		}

		if (ItemName == "")
		{
			return true;
		}

		return false;
	}
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FItemActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	int32 ItemQuantity = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	int32 MaxItemQuantity = 1;
};

USTRUCT(BlueprintType)
struct FOtherItemActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	FName DisplayName = "";
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	UStaticMesh* Mesh = nullptr;
};

USTRUCT(BlueprintType)
struct FAmmoActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	FAmmoActorInfo() { ItemType = EItemType::Ammo_Type; }
};

// Item type:
UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	None_Type UMETA(DisplayName = "None"),
	First_Type UMETA(DisplayName = "First"),
	Second_Type UMETA(DisplayName = "Second")
};

USTRUCT(BlueprintType)
struct FWeaponActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	FName DisplayName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	TSubclassOf<AWeaponMain> WeaponClass = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	EWeaponSlotType WeaponSlotType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	TSoftObjectPtr<UStaticMesh> PickUpMesh = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	FAmmoActorInfo AmmoActorInfo = FAmmoActorInfo();

	FWeaponActorInfo() { ItemType = EItemType::Weapon_Type; };

	virtual bool IsEmpty() const override
	{
		if (ItemType == EItemType::None_Type)
		{
			return true;
		}

		if (ItemName.IsNone())
		{
			return true;
		}

		if (DisplayName.IsNone())
		{
			return true;
		}

		return false;
	}
};

UCLASS()
class TT_269_API UTT_269_Types : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
