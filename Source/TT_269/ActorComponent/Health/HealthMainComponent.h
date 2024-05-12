// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HPPlugin/ActorComponent/HealthComponent.h"
#include "Interface/SavableObject.h"
#include "HealthMainComponent.generated.h"

/**
 *
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API UHealthMainComponent : public UHealthComponent, public ISavableObject
{
	GENERATED_BODY()

#pragma region ISavableObject
	virtual bool GetSaveBinaryData_Implementation(TArray<uint8>& OutBinaryData) override;

	virtual bool LoadSaveBinaryData_Implementation(const TArray<uint8>& NewBinaryData) override;
#pragma endregion
};
