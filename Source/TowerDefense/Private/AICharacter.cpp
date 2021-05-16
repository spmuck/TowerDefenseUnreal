// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if(PatrolPoints.Num() > 0 && bPatrol)
	{
		MoveToNextPatrolPoint();	
	}
}

void AAICharacter::MoveToNextPatrolPoint()
{
	if(CurrentPatrolPoint == nullptr || CurrentPatrolPointIndex >= PatrolPoints.Num()-1)
	{
		CurrentPatrolPointIndex = -1;
	}
	CurrentPatrolPointIndex++;
	CurrentPatrolPoint = PatrolPoints.GetData()[CurrentPatrolPointIndex];
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), CurrentPatrolPoint->GetActorLocation());
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CurrentPatrolPoint && bPatrol)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();

		if(DistanceToGoal < 50)
		{
			MoveToNextPatrolPoint();
		}
	}

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::SetPatrolPoints(TArray<ATargetPoint*> PatrolPointsParam)
{
	PatrolPoints = PatrolPointsParam;
	if(PatrolPoints.Num() > 0 && bPatrol)
	{
		MoveToNextPatrolPoint();	
	}
}

int32 AAICharacter::GetHealth()
{
	return Health;
}

int32 AAICharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AAICharacter>()->GetHealth();
}

void AAICharacter::ApplyDamage(float Damage)
{
	Health -= Damage;
	if(Health <= 0)
	{
		HandleDeath();
	}
}

void AAICharacter::HandleDeath()
{
	Destroy();
}


