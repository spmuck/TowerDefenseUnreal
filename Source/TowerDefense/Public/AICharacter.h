// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToNextPatrolPoint();

	ATargetPoint* CurrentPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category="AI")
	bool bPatrol = true;

	int CurrentPatrolPointIndex;

	TArray<ATargetPoint*> PatrolPoints;

	/** Current health of this Pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float Health = 100.0f;

	void HandleDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetPatrolPoints(TArray<ATargetPoint*> PatrolPointsParam);

	/** get current health */
	UFUNCTION(BlueprintCallable, Category=Health)
	int32 GetHealth();

	/** get max health */
	UFUNCTION(BlueprintCallable, Category=Health)
	int32 GetMaxHealth() const;

	void ApplyDamage(float Damage);

};
