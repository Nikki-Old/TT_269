// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameActorComponent.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "SaveGame/SaveGameMain.h"

USaveGameSubsystem* USaveGameActorComponent::SaveGameSubsytem = nullptr;
USaveGameMain* USaveGameActorComponent::SaveGameObject = nullptr;

// Sets default values for this component's properties
USaveGameActorComponent::USaveGameActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USaveGameActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Is dynamic spawn?
	bIsSpawnedOwner = GetOwner()->GetOuter() ? false : true;

	if (!SaveGameSubsytem)
	{
		LoadSaveGameSubsystem();
	}

	// Bind on delegates:
	if (SaveGameSubsytem)
	{
		// Add tag for owner:
		GetOwner()->Tags.Add(SaveGameSubsytem->GetSaveGameTag());

		// Get current save game object:
		if (!SaveGameObject)
		{
			SaveGameObject = SaveGameSubsytem->GetCurrentSaveGameObject();
		}
	}

	GetOwner()->OnDestroyed.AddDynamic(this, &USaveGameActorComponent::OwnerIsDestroed);
}

void USaveGameActorComponent::OwnerIsDestroed(AActor* DestroyedActor)
{
	if (DestroyedActor == GetOwner())
	{
		SaveGameSubsytem->AddDestroedObject(GetOwner()->GetName());

		GetOwner()->Rename();
	}
}

void USaveGameActorComponent::LoadSaveGameSubsystem()
{
	if (GetWorld())
	{
		// Take GameInstance
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		if (GameInstance)
		{
			// take USaveGameSubsystem
			SaveGameSubsytem = GameInstance->GetSubsystem<USaveGameSubsystem>();

			if (!SaveGameSubsytem)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to get SaveGameSubsytem."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance."));
		}
	}
}

USaveGameSubsystem* USaveGameActorComponent::GetSaveGameSubsystem() const
{
	return SaveGameSubsytem;
}

void USaveGameActorComponent::ChangeSaveGameObject(USaveGameMain* NewSaveGameObject)
{
	if (SaveGameObject != NewSaveGameObject)
	{
		SaveGameObject = NewSaveGameObject;
	}
}

void USaveGameActorComponent::LoadOwnerComponentsBinaryData(const TMap<FString, FActorComponentSaveData>& ComponentsBinaryData)
{

	TSet<UActorComponent*> OwnerComponents = GetOwner()->GetComponents();
	FString ComponentName = "";
	for (const auto Component : OwnerComponents)
	{
		if (Component->GetClass()->ImplementsInterface(USavableObject::StaticClass()))
		{
			ComponentName = Component->GetName();
			if (ComponentsBinaryData.Contains(ComponentName))
			{
				if (ISavableObject::Execute_LoadSaveBinaryData(Component, ComponentsBinaryData[ComponentName].BinaryData))
				{
				}
			}
		}
	}

	OnLoadGameData.Broadcast();
}

void USaveGameActorComponent::GetOwnerComponentsBinaryData(TMap<FString, FActorComponentSaveData>& ComponentsBinaryData)
{
	OnSaveGameData.Broadcast();

	TSet<UActorComponent*> OwnerComponents = GetOwner()->GetComponents();
	TArray<uint8> BinaryData = {};
	FString ComponentName = "";
	for (const auto Component : OwnerComponents)
	{
		if (Component->GetClass()->ImplementsInterface(USavableObject::StaticClass()))
		{
			if (ISavableObject::Execute_GetSaveBinaryData(Component, BinaryData))
			{
				ComponentName = Component->GetName();
				ComponentsBinaryData.Add(ComponentName);
				ComponentsBinaryData[ComponentName].BinaryData = BinaryData;
			}
		}
	}
}

// Called every frame
void USaveGameActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USaveGameActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		SaveGameObject = nullptr;
		SaveGameSubsytem = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

bool USaveGameActorComponent::GetActorSaveData_Implementation(FActorSaveData& SaveData)
{
	FActorSaveData Record = FActorSaveData();

	Record.Class = GetOwner()->GetClass();
	Record.Name = GetOwner()->GetName();
	Record.Transform = GetOwner()->GetTransform();

	FMemoryWriter Writer = FMemoryWriter(Record.ActorBinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	GetOwner()->Serialize(Ar);
	GetOwnerComponentsBinaryData(Record.ActorComponentsBinaryData);
	OnSaveGameData.Broadcast();

	SaveData = Record;

	return true;
}

bool USaveGameActorComponent::LoadActorSaveData_Implementation(const FActorSaveData& SaveData)
{
	FActorSaveData Record = SaveData;

	FMemoryReader Reader = FMemoryReader(Record.ActorBinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	GetOwner()->Serialize(Ar);

	LoadOwnerComponentsBinaryData(Record.ActorComponentsBinaryData);

	GetOwner()->SetActorTransform(Record.Transform);

	OnLoadGameData.Broadcast();

	return true;
}