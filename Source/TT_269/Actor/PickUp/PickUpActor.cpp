// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "ItemDataAsset/ItemDataAsset.h"
#include "FunctionLibrary/TT_269_Types.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create scene component and set root:
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	this->SetRootComponent(SceneComponent);
}

FActorSaveData APickUpActor::GetSaveDataRecord_Implementation()
{
	FActorSaveData Record = FActorSaveData();

	Record.Class = this->GetClass();
	Record.Name = this->GetName();
	Record.Transform = this->GetTransform();

	FMemoryWriter Writer = FMemoryWriter(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	this->Serialize(Ar);

	return Record;
}

void APickUpActor::LoadFromSaveDataRecord_Implementation()
{
	FActorSaveData Record = FActorSaveData();

	FMemoryReader Reader = FMemoryReader(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	this->Serialize(Ar);
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
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
