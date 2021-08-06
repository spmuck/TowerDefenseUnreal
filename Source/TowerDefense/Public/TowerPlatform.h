// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseTower.h"
#include "GameFramework/Actor.h"
#include "TowerPlatform.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;

	ABaseTower* BaseTower;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
