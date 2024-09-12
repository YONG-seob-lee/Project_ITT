// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_GameViewportClient.h"

#include "Manager/ITT_InputManager.h"

namespace DefaultValue
{
	const FVector2D Ratio = FVector2D(0.5f, 0.5f);
}

void UITT_GameViewportClient::Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance,
	bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	gInputMng.GetScreenSplitTypeDelegate().AddUObject(this, &UITT_GameViewportClient::UpdateActiveSplitscreenType);
	gInputMng.GetScreenMoveDelegate().AddUObject(this, &UITT_GameViewportClient::SetSplitScreenInfo);
}

void UITT_GameViewportClient::UpdateActiveSplitscreenType()
{
	ActiveSplitscreenType = ActiveSplitscreenType == ESplitScreenType::TwoPlayer_Vertical ? ESplitScreenType::TwoPlayer_Horizontal : ESplitScreenType::TwoPlayer_Vertical;
	RefreshRatio();
}

void UITT_GameViewportClient::LayoutPlayers()
{
	const ESplitScreenType::Type SplitType = GetCurrentSplitscreenConfiguration();

	// Initialize the players
	const TArray<ULocalPlayer*>& PlayerList = GetOuterUEngine()->GetGamePlayers(this);

	if(PlayerList.Num() == 1)
	{
		for ( int32 PlayerIdx = 0; PlayerIdx < PlayerList.Num(); PlayerIdx++ )
		{
			if ( SplitType < SplitscreenInfo.Num() && PlayerIdx < SplitscreenInfo[SplitType].PlayerData.Num() )
			{
				PlayerList[PlayerIdx]->Size.X =	SplitscreenInfo[SplitType].PlayerData[PlayerIdx].SizeX;
				PlayerList[PlayerIdx]->Size.Y =	SplitscreenInfo[SplitType].PlayerData[PlayerIdx].SizeY;
				PlayerList[PlayerIdx]->Origin.X =	SplitscreenInfo[SplitType].PlayerData[PlayerIdx].OriginX;
				PlayerList[PlayerIdx]->Origin.Y =	SplitscreenInfo[SplitType].PlayerData[PlayerIdx].OriginY;
			}
			else
			{
				PlayerList[PlayerIdx]->Size.X =	0.f;
				PlayerList[PlayerIdx]->Size.Y =	0.f;
				PlayerList[PlayerIdx]->Origin.X =	0.f;
				PlayerList[PlayerIdx]->Origin.Y =	0.f;
			}
		}	
	}
	else if(PlayerList.Num() == 2)
	{
		if(ActiveSplitscreenType == ESplitScreenType::TwoPlayer_Vertical)
		{
			PlayerList[0]->Size.X = SizeRatio.X;
			PlayerList[0]->Size.Y = 1.f;
			PlayerList[0]->Origin.X = 0.f;
			PlayerList[0]->Origin.Y = 0.f;

			PlayerList[1]->Size.X = 1.f - SizeRatio.X;
			PlayerList[1]->Size.Y = 1.f;
			PlayerList[1]->Origin.X = SizeRatio.X;
			PlayerList[1]->Origin.Y = 0.f;
		}
		else if(ActiveSplitscreenType == ESplitScreenType::TwoPlayer_Horizontal)
		{
			PlayerList[0]->Size.X = 1.f;
			PlayerList[0]->Size.Y = SizeRatio.Y;
			PlayerList[0]->Origin.X = 0.f;
			PlayerList[0]->Origin.Y = 0.f;

			PlayerList[1]->Size.X = 1.f;
			PlayerList[1]->Size.Y = 1.f - SizeRatio.Y;
			PlayerList[1]->Origin.X = 0.f;
			PlayerList[1]->Origin.Y = SizeRatio.Y;
		}
			
	}
	
}

void UITT_GameViewportClient::SetSplitScreenInfo(FVector2D MoveVector)
{
	SizeRatio += (MoveVector * 0.01);
}

void UITT_GameViewportClient::RefreshRatio()
{
	SizeRatio = DefaultValue::Ratio;
}
