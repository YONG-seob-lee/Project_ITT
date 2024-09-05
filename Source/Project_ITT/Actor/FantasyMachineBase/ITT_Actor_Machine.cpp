// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Actor_Machine.h"

#include "PROJECT_ITT/ITT_InstUtil.h"

// Sets default values
AITT_Actor_Machine::AITT_Actor_Machine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AITT_Actor_Machine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AITT_Actor_Machine::Tick(float DeltaTime)
{		
}
