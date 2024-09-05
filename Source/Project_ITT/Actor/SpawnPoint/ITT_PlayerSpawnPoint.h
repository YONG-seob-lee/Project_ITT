// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "ITT_PlayerSpawnPoint.generated.h"

namespace DefaultImage
{
	const FString Name = TEXT("DefaultImage");
	const FString PortraitPath_Cody = TEXT("Texture2D'/Game/Texture/Portrait/Portrait_Cody.Portrait_Cody'");
	const FString PortraitPath_May = TEXT("Texture2D'/Game/Texture/Portrait/Portrait_May.Portrait_May'");
	const FString PortraitPath_Rose = TEXT("Texture2D'/Game/Texture/Portrait/Portrait_Rose.Portrait_Rose'");
}

UCLASS()
class PROJECT_ITT_API AITT_PlayerSpawnPoint : public APlayerStart
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	//AITT_PlayerSpawnPoint(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE  FName GetSpawnName() const { return SpawnName; }
	
protected:
	FName SpawnName = FName();
};
