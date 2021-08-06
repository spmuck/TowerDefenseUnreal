// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPlatform.h"

// Sets default values
ATowerPlatform::ATowerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATowerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

