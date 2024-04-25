// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrameworkLibrary.generated.h"

class UGameInstanceMain;
class APlayerControllerMain;

/**
 *
 */

UCLASS()
class TT_269_API UFrameworkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Get Game instance main for this project */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Framework", meta = (WorldContext = "World"))
	static UGameInstanceMain* GetGameInstanceMain(const UObject* World);

	/** Get player controller main by pawn */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Framework")
	static APlayerControllerMain* GetPlayerControllerMain(const APawn* PlayerPawn);
};
