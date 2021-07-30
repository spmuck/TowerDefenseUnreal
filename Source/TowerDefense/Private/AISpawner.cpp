// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAISpawner::AAISpawner()
{
	SecondsBetweenSpawns = 1.0f;
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(TimerHandle_SpawnAI);
	
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnAI, this, &AAISpawner::SpawnAI, SecondsBetweenSpawns);
	
}

void AAISpawner::SpawnAI()
{
	AAICharacter* AICharacter = GetWorld()->SpawnActor<AAICharacter>(AICharacterClass, GetActorTransform());
	AICharacter->SetPatrolPoints(PatrolPoints);
	GetWorldTimerManager().ClearTimer(TimerHandle_SpawnAI);
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnAI, this, &AAISpawner::SpawnAI, SecondsBetweenSpawns);
	
}