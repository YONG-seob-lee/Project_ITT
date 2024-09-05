// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ITTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API AITTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	UPROPERTY()
	TObjectPtr<class AITT_PlayerController> First_Controller = nullptr;

	UPROPERTY()
	TObjectPtr<class AITT_PlayerController> Second_Controller = nullptr;
};
