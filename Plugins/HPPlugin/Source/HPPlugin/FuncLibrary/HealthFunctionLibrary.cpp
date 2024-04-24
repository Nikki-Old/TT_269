// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthFunctionLibrary.h"

ADamageInfo* UHealthFunctionLibrary::SpawnDamageActor(const UObject* WorldContextObject, TSubclassOf<ADamageInfo> DamageClass, FTransform SpawnTransform, const float Health, const float Change, EChangeValueType ChangeValueType)
{
	if (!WorldContextObject && !IsValid(DamageClass))
		return nullptr; // TO DO Check();

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
			EGetWorldErrorMode::LogAndReturnNull))
	{

		auto DamageActor = (World->SpawnActor<ADamageInfo>(DamageClass, SpawnTransform));

		if (DamageActor)
		{
			DamageActor->SetChangeValueType(ChangeValueType);
			DamageActor->UpdateDamageWidget(Health, Change);
		}

		return DamageActor;
	}

	return nullptr;
}