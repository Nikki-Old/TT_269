// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HPPlugin/Actor/DamageInfo.h"
#include "HealthFunctionLibrary.generated.h"

class ADamageInfo;
/**
 *
 */

UCLASS()
class HPPLUGIN_API UHealthFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HealthFunction", meta = (WorldContext = "WorldContextObject"))
	static ADamageInfo* SpawnDamageActor(const UObject* WorldContextObject, TSubclassOf<ADamageInfo> DamageClass, FTransform SpawnTransform, const float Health, const float Change, EChangeValueType ChangeValueType = EChangeValueType::Damage_Type);
};
