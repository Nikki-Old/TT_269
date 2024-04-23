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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Framework", meta = (WorldContext = "World"))
	static UGameInstanceMain* GetGameInstanceMain(const UObject* World);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Framework")
	static APlayerControllerMain* GetPlayerControllerMain(const APawn* PlayerPawn);
};
