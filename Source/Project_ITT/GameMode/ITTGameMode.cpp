// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/ITT_PlayerController.h"

void AITTGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const FString Option = {};
	First_Controller = Cast<AITT_PlayerController>(UGameplayStatics::GetPlayerController(UITT_InstUtil::GetGameWorld(), 0));
	Second_Controller =  Cast<AITT_PlayerController>(SpawnPlayerController(ROLE_MAX, Option));

	AITT_PlayerController* SecondController = Cast<AITT_PlayerController>(UGameplayStatics::GetPlayerController(UITT_InstUtil::GetGameWorld(), 1));
	
	if(First_Controller == SecondController)
	{
		ITT_LOG(TEXT("First And Second Is Same"));
	}

	if(Second_Controller == SecondController)
	{
		ITT_LOG(TEXT("Second_ And Second Is Same"));
	}
}
