// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGame/SaveGameMain.h"

bool USaveGameMain::GetSaveInfoActor(const FName& TargetName, FSaveInfoActor& OutInfo)
{
	if (SaveInfoActors.Num() > 0)
	{
		if (SaveInfoActors.Contains(TargetName))
		{
			OutInfo = SaveInfoActors[TargetName];
			return true;
		}
	}

	return false;
}

bool USaveGameMain::AddSaveInfoActor(const FName& TargetName, const FSaveInfoActor& NewInfo)
{
	if (!TargetName.IsNone())
	{
		SaveInfoActors.Add(TargetName);
		SaveInfoActors[TargetName] = NewInfo;
		return true;
	}

	return false;
}

bool USaveGameMain::GetDynamicSaveInfoActor(const FName& TargetName, FDynamicSaveInfoActor& OutInfo)
{
	if (SaveInfoDynamicActors.Num() > 0)
	{
		if (SaveInfoDynamicActors.Contains(TargetName))
		{
			OutInfo = SaveInfoDynamicActors[TargetName];
			return true;
		}
	}

	return false;
}

bool USaveGameMain::AddDynamicSaveInfoActor(const FName& TargetName, const FDynamicSaveInfoActor& NewInfo)
{
	if (!TargetName.IsNone())
	{
		SaveInfoDynamicActors.Add(TargetName);
		SaveInfoDynamicActors[TargetName] = NewInfo;
		return true;
	}

	return false;
}

bool USaveGameMain::RemoveDynamicSaveInfoActor(const FName& TargetName)
{
	if (SaveInfoDynamicActors.Contains(TargetName))
	{
		SaveInfoDynamicActors.Remove(TargetName);
		return true;
	}

	return false;
}

bool USaveGameMain::GetPlayerCharacterSaveInfo(const FName& TargetName, FPlayerCharacterSaveInfo& OutInfo)
{
	if (PlayersInfo.Contains(TargetName))
	{
		OutInfo = PlayersInfo[TargetName];
		return true;
	}

	return false;
}

bool USaveGameMain::AddPlayerCharacterSaveInfo(const FName& TargetName, const FPlayerCharacterSaveInfo& NewInfo)
{
	if (!TargetName.IsNone())
	{
		PlayersInfo.Add(TargetName);
		PlayersInfo[TargetName] = NewInfo;
		return true;
	}

	return false;
}
