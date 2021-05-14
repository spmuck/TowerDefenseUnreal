// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTower.h"

#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseTower::ABaseTower()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

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
	if(TargetEnemies.Num() > 0)
	{
		AAICharacter* TargetEnemy = TargetEnemies.GetData()[0];
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetEnemy->GetActorLocation());
		SetActorRotation(Rotation);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_FireProjectile, this, &ABaseTower::FireProjectileAtTargetEnemy, SecondsBetweenShots);
}

