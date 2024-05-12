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
	/** Set game byte data */
	UFUNCTION(BlueprintCallable, Category = "SaveGameMain")
	void SetGameByteData(const TArray<uint8>& NewGameByteDate);

	/** Get game byte data */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMain")
	void GetGameByteData(TArray<uint8>& OutInfo);

protected:
	/** All save data from actors */
	UPROPERTY()
	TArray<uint8> GameByteData;
};
