// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "InventoryComponent.generated.h"

class UGameInstanceMain;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateInventorySlot, int32, Index, FInventorySlotInfo, NewInfo);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnUpdateInventorySlot OnUpdateInventorySlot;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	void GetInventoryInfo(TArray<FInventorySlotInfo>& OutInfo) const { OutInfo = InventoryInfo; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int32 IsHaveItemByName(const FName& TargetName, FInventorySlotInfo& OutInventroySlot) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 MaxQuantityInventorySlots = 5;

	bool CreateNewInventorySlot(const FItemActorInfo& NewItemInfo, int32 Quantity);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	static UGameInstanceMain* GameInstanceMain;

	UPROPERTY()
	TArray<FInventorySlotInfo> InventoryInfo = {};
};
