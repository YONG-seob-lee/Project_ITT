// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/ITT_PlayerController.h"

void AITTGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const FString Option = {};
}
