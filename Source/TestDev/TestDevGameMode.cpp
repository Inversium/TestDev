// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestDevGameMode.h"
#include "TestDevCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestDevGameMode::ATestDevGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
