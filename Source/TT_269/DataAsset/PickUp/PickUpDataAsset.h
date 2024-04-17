// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PickUpDataAsset.generated.h"

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

UCLASS()
class TT_269_API UPickUpDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/** Item type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	EItemType ItemType = EItemType::None_Type;

	/** Item name == RowName */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	FName ItemName = "";
	
};
