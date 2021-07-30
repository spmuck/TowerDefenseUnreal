// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenseGameMode.h"
#include "TowerDefensePlayerController.h"
#include "TowerDefenseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATowerDefenseGameMode::ATowerDefenseGameMode()
{
	bGameOver = false;
	// use our custom PlayerController class
	PlayerControllerClass = ATowerDefensePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATowerDefenseGameMode::GameEnd(bool success)
{
	if (!bGameOver)
	{
		bGameOver = true;
		if(!success)
		{
			UGameplayStatics::PlaySound2D(this, LosingSound);
		}
		APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		if(MyPawn)
		{
			MyPawn->DisableInput(nullptr);
		}
	}
	OnGameEnd(success);
}
