// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGame/SaveGameMain.h"

void USaveGameMain::SetGameByteData(const TArray<uint8>& NewGameByteDate)
{
	GameByteData = NewGameByteDate;
}

void USaveGameMain::GetGameByteData(TArray<uint8>& OutInfo)
{
	OutInfo = GameByteData;
}
