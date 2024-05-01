// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

class USaveGameMain;

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeSaveGameObject, USaveGameMain*, NewSaveGameObject);

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

	UPROPERTY(BlueprintAssignable, Category = "SaveGameSubsystem")
	FOnChangeSaveGameObject OnChangeSaveGameObject;

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void CallStartSave();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	TArray<FString> GetAllSaveGames();

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool CreateNewSaveGame(const FString SlotName, TSubclassOf<USaveGame> SaveGameClass, USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SaveGameObject(const FString SlotName, USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool LoadSaveGame(const FString SlotName, USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool DeleteSaveGameSlot(const FString SlotName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	USaveGameMain* GetCurrentSaveGameObject() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	FString GetCurrentSaveGameSlot() const { return CurrentSaveGameSlot; }

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void DeleteAllSaveGameSlots();

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SetCurrentSaveGameObject(const FString SlotName, USaveGame* SaveGameObject);

private:
	UPROPERTY()
	USaveGameMain* CurrentSaveGameObject = nullptr;

	UPROPERTY()
	FString CurrentSaveGameSlot = "";

	UPROPERTY()
	TArray<FString> SaveGameNames;

	uint8 MaxSaveSlot = 8;
};
