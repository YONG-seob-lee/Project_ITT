// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_PlayerSpawnPoint_SelectDummy.h"


// Sets default values
AITT_PlayerSpawnPoint_SelectDummy::AITT_PlayerSpawnPoint_SelectDummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnName = FName("Dummy");
}

// Called when the game starts or when spawned
void AITT_PlayerSpawnPoint_SelectDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AITT_PlayerSpawnPoint_SelectDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

