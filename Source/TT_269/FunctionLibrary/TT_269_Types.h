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

/**
*	Use for base actor
*	If actor on level before game is start.
*/
USTRUCT(BlueprintType)
struct FSaveInfoActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveInfo")
	FTransform Transform = FTransform();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveInfo")
	bool bIsDestroyed = false;
};

USTRUCT(BlueprintType)
struct FDynamicSaveInfoActor : public FSaveInfoActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveInfo")
	TSubclassOf<AActor> Class = nullptr;
};

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

/** Item actor info */
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

/** Inventory slot, child struct "FItemActorInfo" */
USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FItemActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	int32 ItemQuantity = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	int32 MaxItemQuantity = 1;
};

/** Other item actor info, child struct "FInventorySlotInfo" */
USTRUCT(BlueprintType)
struct FOtherItemActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	FName DisplayName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InventorySlotInfo")
	UStaticMesh* Mesh = nullptr;

	FOtherItemActorInfo() { ItemType = EItemType::Other_Type; }
};

/** Projectile info */
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

/** Weapon character animation info */
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

/** Ammo actor info: */
USTRUCT(BlueprintType)
struct FAmmoActorInfo : public FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AmmoActorInfo")
	FName DisplayName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AmmoActorInfo")
	UStaticMesh* Mesh = nullptr;

	FAmmoActorInfo() { ItemType = EItemType::Ammo_Type; }
};

/** Weapon slot type */
UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	None_Type UMETA(DisplayName = "None"),
	First_Type UMETA(DisplayName = "First"),
	Second_Type UMETA(DisplayName = "Second")
};

/** Weapon damage info*/
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

/** Weapon info */
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

/** Main save data record for actors. */
USTRUCT(BlueprintType)
struct FActorSaveData
{
	GENERATED_BODY()

public:
	/** Actor class */
	UPROPERTY(SaveGame)
	UClass* Class = nullptr;

	/** Actor Name */
	UPROPERTY(SaveGame)
	FString Name = "";

	/** Actor transform */
	UPROPERTY(SaveGame)
	FTransform Transform = FTransform();

	/** Other values in the form of binary data */
	UPROPERTY(SaveGame)
	TArray<uint8> BinaryData = {};
};

/** Save info */
USTRUCT(BlueprintType)
struct FPlayerCharacterSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveGame")
	float Health = 0.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveGame")
	TArray<FInventorySlotInfo> InventoryInfo = {};

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveGame")
	TMap<EWeaponSlotType, FWeaponActorInfo> WeaponsInfo = {};
};

///** Save info */
//USTRUCT(BlueprintType)
//struct FTurretSaveInfo
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SaveGame")
//	float 
//};


UCLASS()
class TT_269_API UTT_269_Types : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
