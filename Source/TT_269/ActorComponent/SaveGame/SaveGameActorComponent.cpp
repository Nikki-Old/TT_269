// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameActorComponent.h"
#include "Subsystem/SaveGameSubsystem.h"
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

	bIsDynamicSpawn = GetOwner()->GetOuter() ? false : true;

	if (!SaveGameSubsytem)
	{
		LoadSaveGameSubsystem();
	}

	// Bind on delegates:
	if (SaveGameSubsytem)
	{
		SaveGameSubsytem->OnStartSave.AddDynamic(this, &USaveGameActorComponent::SaveGameData);
		SaveGameSubsytem->OnChangeSaveGameObject.AddDynamic(this, &USaveGameActorComponent::ChangeSaveGameObject);

		// Get current save game object:
		if (!SaveGameObject)
		{
			SaveGameObject = SaveGameSubsytem->GetCurrentSaveGameObject();
		}
	}

	CheckSaveInfoByOwner();

	GetOwner()->OnDestroyed.AddDynamic(this, &USaveGameActorComponent::OwnerIsDestroed);
}

void USaveGameActorComponent::OwnerIsDestroed(AActor* DestroyedActor)
{
	if (DestroyedActor == GetOwner())
	{
		bIsDestroyedOnwer = true;
		SaveGameData();
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

void USaveGameActorComponent::SaveGameData()
{
	if (SaveGameObject)
	{
		if (bIsDynamicSpawn)
		{
			if (bIsDestroyedOnwer)
			{
				SaveGameObject->RemoveDynamicSaveInfoActor(FName(GetOwner()->GetName()));
			}
			else
			{
				FDynamicSaveInfoActor DynamicSaveInfoActor;
				DynamicSaveInfoActor.Class = GetOwner()->GetClass();
				DynamicSaveInfoActor.Transform = GetOwner()->GetActorTransform();
				SaveGameObject->AddDynamicSaveInfoActor(FName(GetOwner()->GetName()), DynamicSaveInfoActor);
			}
		}
		else
		{
			FSaveInfoActor SaveInfoActor;
			SaveInfoActor.bIsDestroyed = bIsDestroyedOnwer;
			SaveInfoActor.Transform = GetOwner()->GetActorTransform();
			SaveGameObject->AddSaveInfoActor(FName(GetOwner()->GetName()), SaveInfoActor);
		}
	}

	OnSaveGameData.Broadcast(SaveGameObject);
}

void USaveGameActorComponent::ChangeSaveGameObject(USaveGameMain* NewSaveGameObject)
{
	if (SaveGameObject != NewSaveGameObject)
	{
		SaveGameObject = NewSaveGameObject;
	}

	// if (!bIsCheckSaveInfo)
	//{
	CheckSaveInfoByOwner();

	OnLoadGameData.Broadcast(NewSaveGameObject);
}

void USaveGameActorComponent::CheckSaveInfoByOwner()
{
	if (SaveGameObject)
	{
		if (bIsDynamicSpawn)
		{
			SaveGameData();
		}
		else
		{
			FSaveInfoActor SaveInfoActor;
			if (SaveGameObject->GetSaveInfoActor(FName(GetOwner()->GetName()), SaveInfoActor))
			{
				if (SaveInfoActor.bIsDestroyed)
				{
					GetOwner()->Destroy();
				}
				else
				{
					GetOwner()->SetActorTransform(SaveInfoActor.Transform);
				}
			}
			else
			{
				SaveGameData();
			}
		}
		bIsCheckSaveInfo = true;
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
