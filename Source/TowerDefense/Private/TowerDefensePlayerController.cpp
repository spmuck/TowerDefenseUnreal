// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefensePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TowerDefenseCharacter.h"
#include "Engine/World.h"

ATowerDefensePlayerController::ATowerDefensePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

int32 ATowerDefensePlayerController::GetGold()
{
	return Gold;
}

void ATowerDefensePlayerController::AddGold(int32 DeltaGold)
{
	Gold += DeltaGold;
	//Yo fuck debt.
	if(Gold < 0)
	{
		Gold = 0;
	}
}

void ATowerDefensePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if(bIsBuildingMode)
	{
		MoveTowerToCursor();
	}
	else if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ATowerDefensePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATowerDefensePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATowerDefensePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATowerDefensePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATowerDefensePlayerController::MoveToTouchLocation);

	//Bind Build Key
	InputComponent->BindAction("BuildMode", IE_Pressed, this, &ATowerDefensePlayerController::onBuildModePressed);
}

void ATowerDefensePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ATowerDefenseCharacter* MyPawn = Cast<ATowerDefenseCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ATowerDefensePlayerController::MoveTowerToCursor()
{
	ATowerDefenseCharacter* MyPawn = Cast<ATowerDefenseCharacter>(GetPawn());
	if(bIsBuildingMode && TowerToBeBuilt && MyPawn)
	{
		TowerToBeBuilt->SetActorLocation(MyPawn->GetCursorToWorld()->GetComponentLocation());
	}
}

void ATowerDefensePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATowerDefensePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATowerDefensePlayerController::OnSetDestinationPressed()
{
	if(bIsBuildingMode)
	{
		bIsBuildingMode = false;
		TowerToBeBuilt->BuildTower();
	}
	else
	{
		bMoveToMouseCursor = true;
	}
	
}

void ATowerDefensePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ATowerDefensePlayerController::onBuildModePressed()
{
	bIsBuildingMode = !bIsBuildingMode;
	if(!bIsBuildingMode)
	{
		return;
	}
	if (ATowerDefenseCharacter* MyPawn = Cast<ATowerDefenseCharacter>(GetPawn()))
	{
		if (Gold >= 100)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			TowerToBeBuilt = GetWorld()->SpawnActor<ABaseTower>(TowerClass, MyPawn->GetCursorToWorld()->GetComponentLocation(), FRotator::ZeroRotator, ActorSpawnParams);
			AddGold(-100);
		}
		else
		{
			bIsBuildingMode = false;
		}
	}
	else
	{
		bIsBuildingMode = false;
	}
}
