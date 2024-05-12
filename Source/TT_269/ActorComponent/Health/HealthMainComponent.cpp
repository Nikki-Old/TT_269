// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthMainComponent.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

bool UHealthMainComponent::GetSaveBinaryData_Implementation(TArray<uint8>& OutBinaryData)
{
	FMemoryWriter Writer = FMemoryWriter(OutBinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	this->Serialize(Ar);
	return true;
}

bool UHealthMainComponent::LoadSaveBinaryData_Implementation(const TArray<uint8>& NewBinaryData)
{
	FMemoryReader Reader = FMemoryReader(NewBinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	this->Serialize(Ar);

	OnChangeHealth.Broadcast(GetOwner(), Health, 0.0f);

	return true;
}
