// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneState_Practice.h"

#include "Manager/ITT_InputManager.h"
#include "Manager/ITT_WidgetManager.h"
#include "Manager/Tool/WidgetTool/ITT_BuiltInWidgetTool.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Actor/SpawnPoint/ITT_PlayerSpawnPoint.h"
#include "PROJECT_ITT/Manager/ITT_CameraManager.h"
#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer_Cody.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer_May.h"
#include "Widget/Aim/ITT_Widget_Aimed.h"

void UITT_SceneState_Practice::Begin()
{
	Super::Begin();
}

void UITT_SceneState_Practice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_SceneState_Practice::Exit()
{
	Super::Exit();
}

bool UITT_SceneState_Practice::LoadingPostProcess(float DeltaTime)
{
	PlayerSpawnPoints.Emplace(UITT_InstUtil::GetSpawnPoint(CharacterName::Cody));
	PlayerSpawnPoints.Emplace(UITT_InstUtil::GetSpawnPoint(CharacterName::May));

	for(const auto& SpawnPoint : PlayerSpawnPoints)
	{
		CreatePlayer(SpawnPoint);
	}

	//ChangeCamera();
	return true;
}

void UITT_SceneState_Practice::CreatePlayer(const TWeakObjectPtr<AITT_PlayerSpawnPoint>& _PlayerSpawnPoint)
{
	if(_PlayerSpawnPoint == nullptr)
	{
		return;
	}
	
	if(Players.Num() > 0)
	{
		ITT_LOG(TEXT("Is Already Has Player Actor. Please check this level!"));
		ResetPlayer();	
	}

	if(_PlayerSpawnPoint->GetSpawnName() == TEXT("Cody"))
	{
		const TObjectPtr<UITT_BasePlayer_Cody> Cody = Cast<UITT_BasePlayer_Cody>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::Cody), UITT_BasePlayer_Cody::StaticClass(), _PlayerSpawnPoint->GetActorLocation(), _PlayerSpawnPoint->GetActorRotation()));
		if(Cody == nullptr)
		{
			return;
		}

		Players.Emplace(Cody);
		Cody->SetSelfPlayer(true);
		Cody->ChangePlayerState(EITT_UnitState::Practice);

		const TObjectPtr<AITT_CharacterBase> CharacterBase = Cody->GetCharacterBase();
		if(!CharacterBase)
		{
			return;
		}
		CharacterBase->GetRootComponent()->ComponentTags.Emplace(FName("Title"));

		UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(Cody));
		UITT_InstUtil::OnPossessUnit(Cast<AITT_CharacterBase>(CharacterBase), 0);
	}
	else if(_PlayerSpawnPoint->GetSpawnName() == TEXT("May"))
	{
		const TObjectPtr<UITT_BasePlayer_May> May = Cast<UITT_BasePlayer_May>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::May), UITT_BasePlayer_May::StaticClass(), _PlayerSpawnPoint->GetActorLocation(), _PlayerSpawnPoint->GetActorRotation()));
		if(May == nullptr)
		{
			return;
		}

		Players.Emplace(May);
		May->SetSelfPlayer(true);
		May->ChangePlayerState(EITT_UnitState::Practice);

		const TObjectPtr<AITT_CharacterBase> CharacterBase = May->GetCharacterBase();
		if(!CharacterBase)
		{
			return;
		}

		CharacterBase->GetRootComponent()->ComponentTags.Emplace(FName("Title"));
		UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(May));
		UITT_InstUtil::OnPossessUnit(Cast<AITT_CharacterBase>(CharacterBase), 1);
	}

	ChangeCamera();
}

void UITT_SceneState_Practice::ResetPlayer()
{
}

void UITT_SceneState_Practice::ChangeCamera()
{
	gCameraMng.ChangeCameraState(static_cast<uint8>(EITT_GameCameraType::Practice));

	TWeakObjectPtr<UITT_BasePlayer_Cody> Cody = nullptr;
	for(const auto& Player : Players)
	{
		if(Player.Get()->GetUnitTableId() == ITT_Character::Cody)
		{
			Cody = Cast<UITT_BasePlayer_Cody>(Player.Get());
		}
	}

	Cody->InitCamera();
}
