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
		if (!bIsSpawnedOwner)
		{
			SaveGameSubsytem->AddDestroedObject(DestroyedActor->GetName());
		}
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

	OnLoadGameData.Broadcast();
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

bool USaveGameActorComponent::GetSaveDataRecord_Implementation(FActorSaveData& SaveData)
{
	FActorSaveData Record = FActorSaveData();

	Record.Class = GetOwner()->GetClass();
	Record.Name = GetOwner()->GetName();
	Record.Transform = GetOwner()->GetTransform();

	FMemoryWriter Writer = FMemoryWriter(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	GetOwner()->Serialize(Ar);
	OnSaveGameData.Broadcast();

	SaveData = Record;

	return true;
}

bool USaveGameActorComponent::LoadFromSaveDataRecord_Implementation(const FActorSaveData& SaveData)
{
	FActorSaveData Record = FActorSaveData();

	FMemoryReader Reader = FMemoryReader(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	GetOwner()->Serialize(Ar);

	GetOwner()->SetActorTransform(SaveData.Transform);

	OnLoadGameData.Broadcast();

	return true;
}