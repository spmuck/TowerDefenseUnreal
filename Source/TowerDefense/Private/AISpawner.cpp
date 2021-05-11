// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(TimerHandle_SpawnAI);
	
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnAI, this, &AAISpawner::SpawnAI, 5.0f);
	
}

void AAISpawner::SpawnAI()
{
	AAICharacter* AICharacter = GetWorld()->SpawnActor<AAICharacter>(AICharacterClass, GetActorTransform());
	AICharacter->SetPatrolPoints(PatrolPoints);
	GetWorldTimerManager().ClearTimer(TimerHandle_SpawnAI);
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnAI, this, &AAISpawner::SpawnAI, 5.0f);
	
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

};

