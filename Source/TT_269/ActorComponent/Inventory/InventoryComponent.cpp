// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponent/Inventory/InventoryComponent.h"
#include "FunctionLibrary/FrameworkLibrary.h"

#include "GameInstance/GameInstanceMain.h"

UGameInstanceMain* UInventoryComponent::GameInstanceMain = nullptr;

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UInventoryComponent::AddItemInfo(const FItemActorInfo& NewItemInfo, int32 Quantity)
{
	if (GameInstanceMain)
	{
		if (InventoryInfo.IsEmpty())
		{
			return CreateNewInventorySlot(NewItemInfo, Quantity);
		}
		else
		{
			FInventorySlotInfo InventroySlot;
			int32 Index = IsHaveItemByName(NewItemInfo.ItemName, InventroySlot);

			if (Index > -1)
			{
				int32 TotalQuantity = InventoryInfo[Index].ItemQuantity + InventroySlot.ItemQuantity;
				if (TotalQuantity > InventroySlot.MaxItemQuantity)
				{
					InventoryInfo[Index].ItemQuantity = InventroySlot.MaxItemQuantity;
		
					if (InventoryInfo.Num() < MaxQuantityInventorySlots)
					{
						return CreateNewInventorySlot(NewItemInfo, TotalQuantity - InventroySlot.MaxItemQuantity);
					}
				}
				else
				{
					InventroySlot.ItemQuantity += Quantity;
					InventoryInfo[Index] = InventroySlot;
				}

				OnUpdateInventorySlot.Broadcast(Index, InventroySlot);
				return true;
			}

			if (InventoryInfo.Num() < MaxQuantityInventorySlots)
			{
				return CreateNewInventorySlot(NewItemInfo, Quantity);
			}
		}
	}

	return false;
}

int32 UInventoryComponent::IsHaveItemByName(const FName& TargetName, FInventorySlotInfo& OutInventroySlot) const
{
	for (int32 i = 0; i < InventoryInfo.Num(); i++)
	{
		if (InventoryInfo[i].ItemName == TargetName)
		{
			OutInventroySlot = InventoryInfo[i];
			return i;
		}
	}

	return -1;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (!GameInstanceMain)
	{
		GameInstanceMain = UFrameworkLibrary::GetGameInstanceMain(GetWorld());
	}
}

bool UInventoryComponent::CreateNewInventorySlot(const FItemActorInfo& NewItemInfo, int32 Quantity)
{
	FInventorySlotInfo NewSlot = FInventorySlotInfo();
	if (GameInstanceMain->GetInventoryInfoByItemInfo(NewItemInfo, NewSlot))
	{
		NewSlot.ItemQuantity += Quantity;

		OnUpdateInventorySlot.Broadcast(InventoryInfo.Add(NewSlot), NewSlot);
		return true;
	}

	return false;
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		GameInstanceMain = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}