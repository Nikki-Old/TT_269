// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

class USaveGameMain;

USTRUCT(BlueprintType)
struct FActorComponentSaveData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TArray<uint8> BinaryData = {};
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
	TArray<uint8> ActorBinaryData = {};

	/** Actor component name and binary data */
	UPROPERTY(SaveGame)
	TMap<FString, FActorComponentSaveData> ActorComponentsBinaryData = {};
};

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

	/** Delegate broadcast start Save actors info */
	UPROPERTY(BlueprintAssignable, Category = "SaveGameSubsystem")
	FOnStartSave OnStartSaveData;

	/** Delegate broadcast in start load new Save data */
	UPROPERTY(BlueprintAssignable, Category = "SaveGameSubsystem")
	FOnChangeSaveGameObject OnStartLoadSaveData;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	TArray<FString> GetAllSaveGames();

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	bool CreateNewSaveGame(const FString SlotName, TSubclassOf<USaveGame> SaveGameClass, USaveGame*& SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SaveGameObject(const FString SlotName, USaveGameMain* SaveGameObject);

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
	void SetCurrentSaveGameObject(const FString SlotName, USaveGameMain* SaveGameObject);

	/** Load actors info */
	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void LoadActorsData();

	/** Save actors info */
	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void SaveActorsInfo();

	/** Get save game tag for actors */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameSubsystem")
	FName GetSaveGameTag() const { return SaveGameTag; }

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void AddDestroedObject(const FString& DestroedObjectName);

	UFUNCTION(BlueprintCallable, Category = "SaveGameSubsystem")
	void ClearDestroedObjectInfromation();

protected:
	/** Actors on level  info */
	UPROPERTY(SaveGame)
	TMap<FString, FActorSaveData> ActorsInfoOnLevel = {};

	/** Spawned actors info */
	UPROPERTY(SaveGame)
	TMap<FString, FActorSaveData> SpawnedActorsInfo = {};

	UPROPERTY(SaveGame)
	TArray<FString> DestroedObjects = {};

	/** Called after async save game data*/
	UFUNCTION()
	void AsyncSaveGameDataIsEnd(const FString& SlotName, const int32 UserIndex, bool bSuccess);

private:
	/** Check is actor in "DestroedObjects" */
	bool IsDestroedActor(FString ActorName) const;

	/** Current Save game info */
	UPROPERTY()
	USaveGameMain* CurrentSaveGameObject = nullptr;
	UPROPERTY()
	FString CurrentSaveGameSlot = "";

	/** Save game tag for actors */
	FName SaveGameTag = "SaveGameActor";

	/** All save game names */
	UPROPERTY()
	TArray<FString> SaveGameNames;

	/** Max save slots */
	uint8 MaxSaveSlots = 8;

	bool bIsStartLoadCurrentSaveGame = false;
};
