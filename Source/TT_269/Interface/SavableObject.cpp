// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SavableObject.h"

// Add default functionality here for any ISavableObject functions that are not pure virtual.

bool ISavableObject::GetSaveDataRecord_Implementation(FActorSaveData& SaveData)
{
	return false;
}

bool ISavableObject::LoadFromSaveDataRecord_Implementation(const FActorSaveData& SaveData)
{
	return false;
}
