// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_PlayerSpawnPoint.h"
#include "ITT_PlayerSpawnPoint_Rose.generated.h"

UCLASS()
class PROJECT_ITT_API AITT_PlayerSpawnPoint_Rose : public AITT_PlayerSpawnPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AITT_PlayerSpawnPoint_Rose();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
