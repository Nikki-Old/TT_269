// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "GameInstanceMain.generated.h"

class UDataTable;

/**
 *
 */
UCLASS()
class TT_269_API UGameInstanceMain : public UGameInstance
{
	GENERATED_BODY()

public:
	/** Get inventory info */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameInstanceMain")
	bool GetInventoryInfoByItemInfo(const FItemActorInfo& ItemActorInfo, FInventorySlotInfo& OutInfo);

	/** Get Ammo info */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameInstanceMain")
	bool GetAmmoInfoByName(const FName& TargetName, FAmmoActorInfo& OutInfo);

	/** Get Weapon Info */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameInstanceMain")
	bool GetWeaponInfoByName(const FName& TargetName, FWeaponActorInfo& OutInfo);

	/** Get Other actor info */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameInstanceMain")
	bool GetOtherActorInfoByName(const FName& TargetName, FOtherItemActorInfo& OutInfo);

protected:
	/** Tables for items */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMain")
	TMap<EItemType, UDataTable*> ItemTables = {};
};
