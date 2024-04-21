// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "ItemDataAsset.generated.h"

/**
 *
 */

UCLASS()
class TT_269_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ItemDataAsset")
	void GetItemInfo(FItemActorInfo& OutInfo) { OutInfo = ItemInfo; }

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ItemDataAsset")
	FItemActorInfo ItemInfo = FItemActorInfo();
};
