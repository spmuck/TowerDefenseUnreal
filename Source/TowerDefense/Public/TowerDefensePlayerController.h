// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BaseTower.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefensePlayerController.generated.h"

UCLASS()
class ATowerDefensePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATowerDefensePlayerController();

	/** get current health */
	UFUNCTION(BlueprintCallable, Category=Health)
	int32 GetGold();

	void AddGold(int32 DeltaGold);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void onBuildModePressed();

	UPROPERTY(EditDefaultsOnly, Category="Build")
	TSubclassOf<ABaseTower> TowerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float Gold = 100.0f;
};


