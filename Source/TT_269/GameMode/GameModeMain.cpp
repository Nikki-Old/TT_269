// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeMain.h"
#include "Kismet/GameplayStatics.h"

#include "Interface/SavableObject.h"

void AGameModeMain::LoadActorsData()
{
}

void AGameModeMain::SaveActorsData()
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);

	for (const auto Actor : FindActors)
	{
		DataRecords.Add(ISavableObject::Execute_GetSaveDataRecord(Actor));
	}
}
