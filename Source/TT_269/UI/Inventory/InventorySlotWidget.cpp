// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "FunctionLibrary/FrameworkLibrary.h"
#include "GameInstance/GameInstanceMain.h"

void UInventorySlotWidget::UpdateInventorySlot_Implementation(const FInventorySlotInfo& NewInventorySlotInfo)
{
	InventorySlotInfo = NewInventorySlotInfo;
}

void UInventorySlotWidget::NativeConstruct()
{
	if (!GameInstanceMain)
	{
		GameInstanceMain = UFrameworkLibrary::GetGameInstanceMain(GetWorld());
	}

	Super::NativeConstruct();
}

const UGameInstanceMain* UInventorySlotWidget::GetGameInstanceMain() const
{
	return GameInstanceMain;
}
