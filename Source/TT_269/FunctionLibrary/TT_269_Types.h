// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "TT_269_Types.generated.h"

class AWeaponMain;
class AWeaponProjectileMain;

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
struct FAmmoActorInfo
{
	GENERATED_BODY()
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
struct FProjectileInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ProjectileInfo")
	TSubclassOf<AWeaponProjectileMain> Class = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ProjectileInfo")
	float Damage = 0.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ProjectileInfo")
	float InitialSpeed = 0.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ProjectileInfo")
	float LifeTime = 0.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ProjectileInfo")
	UStaticMesh* Mesh = nullptr;
};

USTRUCT(BlueprintType)
struct FWeaponDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponDamage")
	bool bIsAutoFire = true;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponDamage")
	float RateOfFire = 0.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponDamage")
	FProjectileInfo ProjectileInfo = FProjectileInfo();
};

USTRUCT(BlueprintType)
struct FCharacterAnimationInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterAnimation")
	UAnimSequence* IdleAnimation = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterAnimation")
	UAnimSequence* RunAnimation = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterAnimation")
	UAnimMontage* AttackAnimMontage = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterAnimation")
	UAnimMontage* ReloadAnimMontage = nullptr;
};

USTRUCT(BlueprintType)
struct FWeaponActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo")
	FName DisplayName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo")
	TSubclassOf<AWeaponMain> WeaponClass = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo")
	EWeaponSlotType WeaponSlotType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo")
	TSoftObjectPtr<UStaticMesh> PickUpMesh = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo")
	FName AttachSocketName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo | Ammo")
	FAmmoActorInfo AmmoActorInfo = FAmmoActorInfo();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo | Ammo")
	int32 MaxAmmo = 0;

	UPROPERTY(BlueprintReadWrite, Category = "WeaponActorInfo | Ammo")
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo | Animation")
	FCharacterAnimationInfo CharacterAnimation = FCharacterAnimationInfo();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WeaponActorInfo | Animation")
	FWeaponDamageInfo WeaponDamageInfo = FWeaponDamageInfo();

	FWeaponActorInfo() { ItemType = EItemType::Weapon_Type; };

	virtual bool IsEmpty() const override
	{

		if (DisplayName.IsNone())
		{
			return true;
		}

		return Super::IsEmpty();
	}
};

UCLASS()
class TT_269_API UTT_269_Types : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
