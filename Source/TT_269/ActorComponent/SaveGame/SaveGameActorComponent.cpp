// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponent/SaveGame/SaveGameActorComponent.h"
#include "Subsystem/SaveGameSubsystem.h"

USaveGameSubsystem* USaveGameActorComponent::SaveGameSubsytem = nullptr;

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

	if (!SaveGameSubsytem)
	{
		LoadSaveGameSubsystem();
	}

	if (SaveGameSubsytem)
	{
		SaveGameSubsytem->OnStartSave.AddDynamic(this, &USaveGameActorComponent::OnSaveGameData);
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

void USaveGameActorComponent::OnSaveGameData()
{
	OnUpdateSaveGameData.Broadcast(true, FName(GetOwner()->GetName()), SaveGameSubsytem);
}

// Called every frame
void USaveGameActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
