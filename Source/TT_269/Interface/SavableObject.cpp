// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SavableObject.h"

// Add default functionality here for any ISavableObject functions that are not pure virtual.

bool ISavableObject::GetActorSaveData_Implementation(FActorSaveData& SaveData)
{
	return false;
}

bool ISavableObject::LoadActorSaveData_Implementation(const FActorSaveData& SaveData)
{
	return false;
}

bool ISavableObject::GetSaveBinaryData_Implementation(TArray<uint8>& OutBinaryData)
{
	return false;
}

bool ISavableObject::LoadSaveBinaryData_Implementation(const TArray<uint8>& NewBinaryData)
{
	return false;
}
