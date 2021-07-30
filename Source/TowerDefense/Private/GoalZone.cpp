// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalZone.h"

#include "AICharacter.h"
#include "TowerDefenseGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AGoalZone::AGoalZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AGoalZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->DecalSize = FVector(200.0f,200.0f,200.0f);
	DecalComponent->SetupAttachment(RootComponent);

}

void AGoalZone::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter* EnemyCharacter = Cast<AAICharacter>(OtherActor);
	if(EnemyCharacter != nullptr)
	{
		HandleEnemyEnterZone();
		OtherActor->Destroy();
	}
	
}

void AGoalZone::HandleEnemyEnterZone()
{
	Health--;
	if(Health <= 0)
	{
		ATowerDefenseGameMode* GM = Cast<ATowerDefenseGameMode>( GetWorld()->GetAuthGameMode());
		if(GM)
		{
			GM->GameEnd(false);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Enemy Reached Zone. Health Left: %d"), Health);
}
