// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "GameModeMain.generated.h"

/**
 *
 */
UCLASS()
class TT_269_API AGameModeMain : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Load  */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void LoadActorsData();

	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SaveActorsData();

protected:
	TArray<FActorSaveData> DataRecords = {};
};
