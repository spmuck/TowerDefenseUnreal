// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AICharacter.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS()
class TOWERDEFENSE_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<AAICharacter> AICharacterClass;
	FTimerHandle TimerHandle_SpawnAI;
	void SpawnAI();
	UPROPERTY(EditInstanceOnly, Category="AI")
	TArray<ATargetPoint*> PatrolPoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
