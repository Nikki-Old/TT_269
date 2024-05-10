// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "SavableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USavableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TT_269_API ISavableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Get */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	bool GetSaveDataRecord(FActorSaveData& SaveData);
	virtual bool GetSaveDataRecord_Implementation(FActorSaveData& SaveData);

	/** Set */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	bool LoadFromSaveDataRecord(const FActorSaveData& SaveData);
	virtual bool LoadFromSaveDataRecord_Implementation(const FActorSaveData& SaveData);
};
