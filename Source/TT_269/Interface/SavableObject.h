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
	/** Get actor save data struct. Use for actors. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	bool GetActorSaveData(FActorSaveData& SaveData);
	virtual bool GetActorSaveData_Implementation(FActorSaveData& SaveData);

	/** Set actor save data struct. Use for actors. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	bool LoadActorSaveData(const FActorSaveData& SaveData);
	virtual bool LoadActorSaveData_Implementation(const FActorSaveData& SaveData);

	UFUNCTION(BlueprintNativeEvent, Category = "SaveLoad")
	bool GetSaveBinaryData(TArray<uint8>& OutBinaryData);
	virtual bool GetSaveBinaryData_Implementation(TArray<uint8>& OutBinaryData);

	UFUNCTION(BlueprintNativeEvent, Category = "SaveLoad")
	bool LoadSaveBinaryData(const TArray<uint8>& NewBinaryData);
	virtual bool LoadSaveBinaryData_Implementation(const TArray<uint8>& NewBinaryData);
};
