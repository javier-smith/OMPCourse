// Copyright Epic Games, Inc. All Rights Reserved.

#include "OMPCourseGameMode.h"
#include "OMPCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOMPCourseGameMode::AOMPCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
