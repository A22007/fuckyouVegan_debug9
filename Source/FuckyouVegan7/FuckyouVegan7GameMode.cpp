// Copyright Epic Games, Inc. All Rights Reserved.

#include "FuckyouVegan7GameMode.h"
#include "FuckyouVegan7Character.h"
#include "UObject/ConstructorHelpers.h"

AFuckyouVegan7GameMode::AFuckyouVegan7GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
