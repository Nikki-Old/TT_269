// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SavableObject.h"

// Add default functionality here for any ISavableObject functions that are not pure virtual.

FActorSaveData ISavableObject::GetSaveDataRecord_Implementation()
{
	return FActorSaveData();
}

void ISavableObject::LoadFromSaveDataRecord_Implementation()
{
}
