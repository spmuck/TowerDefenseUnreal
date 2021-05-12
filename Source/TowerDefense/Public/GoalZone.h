// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalZone.generated.h"

class UBoxComponent;
UCLASS()
class TOWERDEFENSE_API AGoalZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalZone();

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UDecalComponent* DecalComponent;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UBoxComponent* OverlapComp;
	UFUNCTION()
	void HandleOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	void HandleEnemyEnterZone();

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	USoundBase* ObjectiveMissingSound;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay")
	int Health = 10;
};
