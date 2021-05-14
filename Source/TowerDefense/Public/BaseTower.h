// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "BaseTower.generated.h"

class USphereComponent;
UCLASS()
class TOWERDEFENSE_API ABaseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* TargetEnemy;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* TowerAttackSphereComp;

	UPROPERTY(EditAnywhere, Category="Components")
	float TowerAttackSphereRadius = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TSubclassOf<AProjectile> ProjectileClass;

	UFUNCTION()
	void OnEnemyOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void FireProjectileAtTargetEnemy(AActor* OtherActor);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
