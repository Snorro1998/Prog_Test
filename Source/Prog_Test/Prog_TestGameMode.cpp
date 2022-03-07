// Copyright Epic Games, Inc. All Rights Reserved.

#include "Prog_TestGameMode.h"
#include "Prog_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProg_TestGameMode::AProg_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
