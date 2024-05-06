// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "SaveGameMain.generated.h"

/**
 *
 */
UCLASS()
class TT_269_API USaveGameMain : public USaveGame
{
	GENERATED_BODY()

public:
	/** Get FSaveInfoActor by name*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMain")
	bool GetSaveInfoActor(const FName& TargetName, FSaveInfoActor& OutInfo);

	/** Get FSaveInfoActor by name*/
	UFUNCTION(BlueprintCallable, Category = "SaveGameMain")
	bool AddSaveInfoActor(const FName& TargetName, const FSaveInfoActor& NewInfo);

	/** Get FDynamicSaveInfoActor by name*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMain")
	bool GetDynamicSaveInfoActor(const FName& TargetName, FDynamicSaveInfoActor& OutInfo);

	/** Get FDynamicSaveInfoActor by name*/
	UFUNCTION(BlueprintCallable, Category = "SaveGameMain")
	bool AddDynamicSaveInfoActor(const FName& TargetName, const FDynamicSaveInfoActor& NewInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMain")
	bool RemoveDynamicSaveInfoActor(const FName& TargetName);

	/** Get FPlayerCharacterSaveInfo by name*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMain")
	bool GetPlayerCharacterSaveInfo(const FName& TargetName, FPlayerCharacterSaveInfo& OutInfo);

	/** Get FPlayerCharacterSaveInfo by name*/
	UFUNCTION(BlueprintCallable, Category = "SaveGameMain")
	bool AddPlayerCharacterSaveInfo(const FName& TargetName, const FPlayerCharacterSaveInfo& NewInfo);

private:
	UPROPERTY()
	TMap<FName, FPlayerCharacterSaveInfo> PlayersInfo = {};

	UPROPERTY()
	TMap<FName, FSaveInfoActor> SaveInfoActors = {};

	UPROPERTY()
	TMap<FName, FDynamicSaveInfoActor> SaveInfoDynamicActors = {};
};
