// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSave);

UCLASS()
class TT_269_API USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UPROPERTY(BlueprintAssignable, Category = "SaveGameSubsystem")
	FOnStartSave OnStartSave;

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void CallStartSave();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	TArray<FString> GetAllSaveGames();

	// UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	// bool GetSaveGamesByTarget(FString TargetName, TArray<FString>& OutInfo);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool CreateNewSaveGame(const FString SlotName, TSubclassOf<USaveGame> SaveGameClass, USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SaveGameObject(const FString SlotName, USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool LoadSaveGame(const FString SlotName, USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool DeleteSaveGameSlot(const FString SlotName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	USaveGame* GetCurrentSaveGameObject() const;

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void DeleteAllSaveGameSlots();
	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SetCurrentSaveGameObject(const FString SlotName, USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	FString GetCurrentSaveGameSlot() const { return CurrentSaveGameSlot; }

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool LoadSaveSettingsData(USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	USaveGame* GetSaveSettingsData() const { return SaveSettingsObject; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	void GetSaveSettingsDataName(FString& OutInfo) const { OutInfo = SaveSettingsDataName; }

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool LoadSaveCollectiblesData(USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	void GetSaveCollectibleDataName(FString& OutInfo) const { OutInfo = SaveCollectiblesDataName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	USaveGame* GetSaveCollectiblesData() const { return SaveCollectiblesObject; }

private:
	UPROPERTY()
	FString SaveSettingsDataName = "Settings";

	UPROPERTY()
	USaveGame* SaveSettingsObject = nullptr;

	UPROPERTY()
	FString SaveCollectiblesDataName = "Collectibles";

	UPROPERTY()
	USaveGame* SaveCollectiblesObject = nullptr;

	UPROPERTY()
	USaveGame* CurrentSaveGameObject = nullptr;

	UPROPERTY()
	FString CurrentSaveGameSlot = "";

	// UPROPERTY()
	// TArray<FString> AvaiableSaveGames;

	UPROPERTY()
	TArray<FString> SaveGameNames;

	uint8 MaxSaveSlot = 8;
};
