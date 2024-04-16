// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerMain.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerMain::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup Input mapping:
	if (InputComponent)
	{
		UEnhancedInputLocalPlayerSubsystem* SubsystemInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (SubsystemInput)
		{
			SubsystemInput->ClearAllMappings();
			SubsystemInput->AddMappingContext(InputMapping, 0);
		}
	}
}
