// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "InventorySlotWidget.generated.h"

class UGameInstanceMain;

/**
 *
 */

UCLASS()
class TT_269_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InventorySlot")
	void UpdateInventorySlot(const FInventorySlotInfo& NewInventorySlotInfo);
	void UpdateInventorySlot_Implementation(const FInventorySlotInfo& NewInventorySlotInfo);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "InventorySlot", meta = (ExposeOnSpawn = true))
	FInventorySlotInfo InventorySlotInfo;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot")
	const UGameInstanceMain* GetGameInstanceMain() const;

	UPROPERTY()
	UGameInstanceMain* GameInstanceMain;
};
