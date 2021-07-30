// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameMode.generated.h"

UCLASS(minimalapi)
class ATowerDefenseGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LosingSound;
	bool bGameOver;

public:
	ATowerDefenseGameMode();
	void GameEnd(bool success);

	UFUNCTION(BlueprintImplementableEvent, Category="Game")
	void OnGameEnd(bool success);
};



