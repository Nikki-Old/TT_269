// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerMain.generated.h"

/**
 *
 */
class UInputMappingContext;

UCLASS()
class TT_269_API APlayerControllerMain : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerController | Inputs")
	void SetInputMapping(UInputMappingContext* NewInputMapping);

protected:
	virtual void SetupInputComponent() override;

	/** MappingContext for player input. */
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputMappingContext* CurrentInputMapping = nullptr;
};
