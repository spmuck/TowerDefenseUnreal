// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseTower.h"
#include "GameFramework/Actor.h"
#include "TowerLocation.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UStaticMeshComponent* MeshComp;
	ABaseTower* Tower;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
