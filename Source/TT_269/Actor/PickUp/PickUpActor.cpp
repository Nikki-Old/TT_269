// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpActor.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "ItemDataAsset/ItemDataAsset.h"
#include "FunctionLibrary/TT_269_Types.h"

#include "ActorComponent/SaveGame/SaveGameActorComponent.h"
#include "SaveGame/SaveGameMain.h"

// Sets default values
APickUpActor::APickUpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create scene component and set root:
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	this->SetRootComponent(SceneComponent);

	// Create save game actor component:
	SaveGameComponent = CreateDefaultSubobject<USaveGameActorComponent>(TEXT("SaveGameComponent"));
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void APickUpActor::Initialize_Implementation()
{
	// In BP
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APickUpActor::IsCanInteract_Implementation() const
{
	return false;
}

bool APickUpActor::ShowCanInteract_Implementation()
{
	return false;
}

bool APickUpActor::UnShowCanInteract_Implementation()
{
	return false;
}

bool APickUpActor::StartInteract_Implementation(AActor* InteractInstigator)
{
	return false;
}

bool APickUpActor::StopInteract_Implementation()
{
	return false;
}
