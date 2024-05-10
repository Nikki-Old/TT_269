// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameSubsystem.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "SaveGame/SaveGameMain.h"
#include "SaveGame/SaveGameActorComponent.h"
#include "Interface/SavableObject.h"

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

TArray<FString> USaveGameSubsystem::GetAllSaveGames()
{

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
		}
	}

	return SaveGameNames;
}

bool USaveGameSubsystem::CreateNewSaveGame(const FString SlotName, TSubclassOf<USaveGame> SaveGameClass, USaveGame*& SaveGameObject)
{
	if (!SlotName.IsEmpty())
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		if (UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0))
		{

			SaveGameNames.AddUnique(SlotName);

			return true;
		}
	}

	return false;
}

void USaveGameSubsystem::SaveGameObject(const FString SlotName, USaveGameMain* SaveGameObject)
{
	if (!SlotName.IsEmpty() && SaveGameObject)
	{
		// Get actors info for save:
		SaveActorsInfo();

		// Create binary data for this object:
		TArray<uint8> BinaryData;
		FMemoryWriter Writer = FMemoryWriter(BinaryData);
		FObjectAndNameAsStringProxyArchive Archive(Writer, false);
		Archive.ArIsSaveGame = true;
		Archive.ArNoDelta = true;
		this->Serialize(Archive);

		// Set binary data in save game object:
		SaveGameObject->SetGameByteData(BinaryData);

		// Start async save game:
		FAsyncSaveGameToSlotDelegate AsyncSaveGameArchive;
		AsyncSaveGameArchive.BindUObject(this, &USaveGameSubsystem::AsyncSaveGameDataIsEnd);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, SlotName, 0, AsyncSaveGameArchive);
	}
}

bool USaveGameSubsystem::LoadSaveGame(const FString SlotName, USaveGame*& SaveGameObject)
{
	SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	return SaveGameObject ? true : false;
}

bool USaveGameSubsystem::DeleteSaveGameSlot(const FString SlotName)
{
	if (SlotName.IsEmpty())
	{
		return false;
	}

	if (SaveGameNames.Find(SlotName) > -1)
	{
		SaveGameNames.Remove(SlotName);
	}

	return UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

USaveGameMain* USaveGameSubsystem::GetCurrentSaveGameObject() const
{
	return CurrentSaveGameObject;
}

void USaveGameSubsystem::DeleteAllSaveGameSlots()
{
	for (const auto SaveGameName : SaveGameNames)
	{
		UGameplayStatics::DeleteGameInSlot(SaveGameName, 0);
	}
	SaveGameNames.Empty();
}

void USaveGameSubsystem::SetCurrentSaveGameObject(const FString SlotName, USaveGameMain* SaveGameObject)
{
	CurrentSaveGameObject = SaveGameObject;
	CurrentSaveGameSlot = SlotName;

	LoadActorsData();
}

void USaveGameSubsystem::LoadActorsData()
{
	OnStartLoadSaveData.Broadcast(CurrentSaveGameObject);

	TArray<AActor*> FindActors;

	// Get info:
	TArray<uint8> BinaryData = {};
	CurrentSaveGameObject->GetGameByteData(BinaryData);

	FMemoryReader Reader = FMemoryReader(BinaryData);
	FObjectAndNameAsStringProxyArchive Arhive(Reader, false);
	Arhive.ArIsSaveGame = true;
	Arhive.ArNoDelta = true;
	Serialize(Arhive);

	{
		FString ActorName = "";
		// Load actors with "USaveGameActorComponent":
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), SaveGameTag, FindActors);
		for (const auto Actor : FindActors)
		{
			ActorName = Actor->GetName();
			if (IsDestroedActor(ActorName))
			{
				Actor->Destroy();
			}
			else
			{
				auto SaveComp = Actor->GetComponentByClass<USaveGameActorComponent>();
				if (SaveComp)
				{

					if (ActorsInfoOnLevel.Contains(ActorName))
					{
						if (ISavableObject::Execute_LoadFromSaveDataRecord(SaveComp, ActorsInfoOnLevel[ActorName]))
						{
							// true
						}
					}
				}
			}
		}

		// Load save info actors with "USavableObject" interface:
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
		for (const auto Actor : FindActors)
		{
			ActorName = Actor->GetName();
			if (IsDestroedActor(ActorName))
			{
				Actor->Destroy();
			}
			else
			{
				if (ActorsInfoOnLevel.Contains(ActorName))
				{
					if (ISavableObject::Execute_LoadFromSaveDataRecord(Actor, ActorsInfoOnLevel[ActorName]))
					{
						// true
					}
				}
			}
		}
	}

	for (const auto& ActorInfo : SpawnedActorsInfo)
	{
		FActorSpawnParameters SpawnParam = FActorSpawnParameters();
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.Name = FName(ActorInfo.Value.Name);
		GetWorld()->SpawnActor<AActor>(ActorInfo.Value.Class, ActorInfo.Value.Transform, SpawnParam);
	}

	// Clear after load:
	ActorsInfoOnLevel.Empty();
}

void USaveGameSubsystem::SaveActorsInfo()
{
	if (GetCurrentSaveGameObject())
	{
		ActorsInfoOnLevel.Empty();

		OnStartSaveData.Broadcast();

		TArray<AActor*> FindActors;

		// Save actors with "USaveGameActorComponent":
		FActorSaveData ActorSaveData = FActorSaveData();
		FString ActorName = "";
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), SaveGameTag, FindActors);
		for (const auto Actor : FindActors)
		{
			ActorName = Actor->GetName();
			auto SaveComp = Actor->GetComponentByClass<USaveGameActorComponent>();
			if (SaveComp)
			{
				if (ISavableObject::Execute_GetSaveDataRecord(SaveComp, ActorSaveData))
				{
					bool bIsSpawnedActor = Actor->GetOuter() ? false : true;
					if (bIsSpawnedActor)
					{
						SpawnedActorsInfo.Add(ActorName);
						SpawnedActorsInfo[ActorName] = ActorSaveData;
					}
					else
					{
						ActorsInfoOnLevel.Add(ActorName);
						ActorsInfoOnLevel[ActorName] = ActorSaveData;
					}
				}
			}
		}

		// Save actors with "USavableObject" interface:
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
		for (const auto Actor : FindActors)
		{
			ActorName = Actor->GetName();
			if (ISavableObject::Execute_GetSaveDataRecord(Actor, ActorSaveData))
			{
				bool bIsSpawnedActor = Actor->GetOuter() ? false : true;
				if (bIsSpawnedActor)
				{
					SpawnedActorsInfo.Add(ActorName);
					SpawnedActorsInfo[ActorName] = ActorSaveData;
				}
				else
				{
					ActorsInfoOnLevel.Add(ActorName);
					ActorsInfoOnLevel[ActorName] = ActorSaveData;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogSaveGameSubsystem, Warning, TEXT("OnStartSave - FAILED! Current save game object is not valid!"));
	}
}

void USaveGameSubsystem::AddDestroedObject(const FString& DestroedObjectName)
{
	DestroedObjects.Add(DestroedObjectName);
}

void USaveGameSubsystem::ClearDestroedObjectInfromation()
{
	DestroedObjects.Empty();
}

void USaveGameSubsystem::AsyncSaveGameDataIsEnd(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	// Clear old info:
	ActorsInfoOnLevel.Empty();
	SpawnedActorsInfo.Empty();
}

bool USaveGameSubsystem::IsDestroedActor(FString ActorName) const
{
	return DestroedObjects.Contains(ActorName);
}
