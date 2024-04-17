// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerMain.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerMain::SetInputMapping(UInputMappingContext* NewInputMapping)
{
	if (NewInputMapping && CurrentInputMapping != NewInputMapping)
	{
		CurrentInputMapping = NewInputMapping;
		// Setup Input mapping:
		if (InputComponent)
		{
			UEnhancedInputLocalPlayerSubsystem* SubsystemInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

			if (SubsystemInput)
			{
				SubsystemInput->ClearAllMappings();
				SubsystemInput->AddMappingContext(CurrentInputMapping, 0);
			}
		}
	}
}

void APlayerControllerMain::SetupInputComponent()
{
	Super::SetupInputComponent();
}
