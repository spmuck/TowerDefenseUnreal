// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTower.h"

#include "AICharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseTower::ABaseTower()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	TowerAttackSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("TowerAttackSphereComp"));
	TowerAttackSphereComp->SetSphereRadius(TowerAttackSphereRadius);
	TowerAttackSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	TowerAttackSphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TowerAttackSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseTower::OnEnemyOverlapBegin);
	TowerAttackSphereComp->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABaseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTower::OnEnemyOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//skip logic if other actor is a null pointer, or we currently have a target.
	if(OtherActor == nullptr || TargetEnemy != nullptr)
	{
		return;
	}
	AAICharacter* EnemyCharacter = Cast<AAICharacter>(OtherActor);
	if(EnemyCharacter)
	{
		TargetEnemy = EnemyCharacter;
		FireProjectileAtTargetEnemy(OtherActor);
	}
	
}

void ABaseTower::FireProjectileAtTargetEnemy(AActor* OtherActor)
{
	FVector direction = OtherActor->GetActorLocation() - GetActorLocation();
	direction.Normalize();
	direction *= 50.0f;
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation() + direction, GetActorRotation() );
}

