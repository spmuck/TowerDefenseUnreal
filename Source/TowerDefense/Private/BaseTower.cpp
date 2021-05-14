// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTower.h"

#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseTower::ABaseTower()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	TowerAttackSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("TowerAttackSphereComp"));
	TowerAttackSphereComp->SetSphereRadius(TowerAttackSphereRadius);
	TowerAttackSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	TowerAttackSphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TowerAttackSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseTower::OnEnemyOverlapBegin);
	TowerAttackSphereComp->OnComponentEndOverlap.AddDynamic(this, &ABaseTower::OnEnemyOverlapEnd);
	TowerAttackSphereComp->SetupAttachment(RootComponent);
}

void ABaseTower::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_FireProjectile, this, &ABaseTower::FireProjectileAtTargetEnemy, SecondsBetweenShots);
}

void ABaseTower::OnEnemyOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                     class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter* EnemyCharacter = Cast<AAICharacter>(OtherActor);
	if(EnemyCharacter && !TargetEnemies.Contains(EnemyCharacter))
	{
		TargetEnemies.Push(EnemyCharacter);
	}
	
}

void ABaseTower::OnEnemyOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAICharacter* EnemyCharacter = Cast<AAICharacter>(OtherActor);
	if(EnemyCharacter && TargetEnemies.Contains(EnemyCharacter))
	{
		TargetEnemies.Remove(EnemyCharacter);
	}
}

void ABaseTower::FireProjectileAtTargetEnemy()
{
	
	GetWorldTimerManager().SetTimer(TimerHandle_FireProjectile, this, &ABaseTower::FireProjectileAtTargetEnemy, SecondsBetweenShots);
}

void ABaseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TargetEnemies.Num() > 0)
	{
		AAICharacter* TargetEnemy = TargetEnemies.GetData()[0];
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetEnemy->GetActorLocation());
		//We only want to change the tower's yaw to make it point at enemy.
		Rotation.Pitch = 0.0f;
		Rotation.Roll = 0.0f;
		SetActorRotation(Rotation);
	}
}

