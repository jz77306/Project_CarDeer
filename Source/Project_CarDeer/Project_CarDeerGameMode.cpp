// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_CarDeerGameMode.h"
#include "Project_CarDeerPlayerController.h"
#include "Project_CarDeerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_CarDeerGameMode::AProject_CarDeerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProject_CarDeerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Player/BP_CarDeerPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}