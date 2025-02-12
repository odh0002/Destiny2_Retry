// Copyright Epic Games, Inc. All Rights Reserved.

#include "Destiny2GameMode.h"
#include "Destiny2Character.h"
#include "UObject/ConstructorHelpers.h"

ADestiny2GameMode::ADestiny2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
