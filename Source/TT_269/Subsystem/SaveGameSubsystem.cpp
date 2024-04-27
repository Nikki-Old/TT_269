// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameSubsystem.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"

// Create log for this class:
DEFINE_LOG_CATEGORY_STATIC(LogSaveGameSubsystem, All, All)

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Pull SaveGame data:
	GetAllSaveGames();
}

void USaveGameSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void USaveGameSubsystem::CallStartSave()
{
	if (GetCurrentSaveGameObject())
	{
		OnStartSave.Broadcast();
	}
	else
	{
		UE_LOG(LogSaveGameSubsystem, Warning, TEXT("OnStartSave - FAILED! Current save game object is not valid!"));
	}
}

TArray<FString> USaveGameSubsystem::GetAllSaveGames()
{
	//AvaiableSaveGames = {};

	if (SaveGameNames.Num() <= 0)
	{
		// Path to all save game data:
		FString SaveDirectory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveGames"));

		TArray<FString> FoundFiles;
		IFileManager::Get().FindFiles(FoundFiles, *SaveDirectory, TEXT("*.sav"));

		for (const auto& FoundFile : FoundFiles)
		{
			const auto IndexFormat = FoundFile.Find(".sav");
			auto FileName = FoundFile.Mid(0, IndexFormat);
			SaveGameNames.Add(FileName);

			//if (FileName != SaveSettingsDataName && FileName != SaveCollectiblesDataName)
			//{
			//	AvaiableSaveGames.Add(FileName);
			//}
		}
	}

	return SaveGameNames;
}

// bool USaveGameSubsystem::GetSaveGamesByTarget(FString TargetName, TArray<FString>& OutInfo)
//{
//	if (SaveGameNames.Num() > 0)
//	{
//		for (const auto SaveGameName : SaveGameNames)
//		{
//			if (SaveGameName.Find(TargetName) > -1)
//			{
//				OutInfo.AddUnique(SaveGameName);
//			}
//		}
//
//		return true;
//	}
//
//	return false;
// }

bool USaveGameSubsystem::CreateNewSaveGame(const FString SlotName, TSubclassOf<USaveGame> SaveGameClass, USaveGame*& SaveGameObject)
{
	if (!SlotName.IsEmpty())
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		if (UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0))
		{
			// if (SaveGameNames.Num() >= MaxSaveSlot)
			//{
			//	DeleteSaveGameSlot(SaveGameNames[0]);
			// }

			SaveGameNames.AddUnique(SlotName);

			return true;
		}
	}

	return false;
}

void USaveGameSubsystem::SaveGameObject(const FString SlotName, USaveGame* SaveGameObject)
{
	if (!SlotName.IsEmpty())
	{
		UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0);
	}
}

bool USaveGameSubsystem::LoadSaveGame(const FString SlotName, USaveGame*& SaveGameObject)
{
	SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, 0);	
	return SaveGameObject ? true : false;
}

bool USaveGameSubsystem::DeleteSaveGameSlot(const FString SlotName)
{
	if (SlotName.IsEmpty() && SlotName != SaveSettingsDataName && SlotName != SaveCollectiblesDataName)
	{
		return false;
	}

	if (SaveGameNames.Find(SlotName) > -1)
	{
		SaveGameNames.Remove(SlotName);
	}

	return UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

USaveGame* USaveGameSubsystem::GetCurrentSaveGameObject() const
{
	return CurrentSaveGameObject;
}

void USaveGameSubsystem::DeleteAllSaveGameSlots()
{
	for (const auto SaveGameName : SaveGameNames)
	{
		if (SaveGameName != SaveSettingsDataName && SaveGameName != SaveCollectiblesDataName)
		{
			UGameplayStatics::DeleteGameInSlot(SaveGameName, 0);
		}
	}
	SaveGameNames.Empty();
}

void USaveGameSubsystem::SetCurrentSaveGameObject(const FString SlotName, USaveGame* SaveGameObject)
{
	CurrentSaveGameObject = SaveGameObject;
	CurrentSaveGameSlot = SlotName;
}

bool USaveGameSubsystem::LoadSaveSettingsData(USaveGame*& SaveGameObject)
{
	SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSettingsDataName, 0);
	SaveSettingsObject = SaveGameObject;

	return SaveSettingsObject ? true : false;
}

bool USaveGameSubsystem::LoadSaveCollectiblesData(USaveGame*& SaveGameObject)
{
	SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveCollectiblesDataName, 0);
	SaveCollectiblesObject = SaveGameObject;

	return SaveCollectiblesObject ? true : false;
}
