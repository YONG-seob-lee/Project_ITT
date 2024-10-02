// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneState_Chapter01.h"

#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Actor/SpawnPoint/ITT_PlayerSpawnPoint.h"
#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer_Cody.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer_May.h"

void UITT_SceneState_Chapter01::Begin()
{
	Super::Begin();
}

void UITT_SceneState_Chapter01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_SceneState_Chapter01::Exit()
{
	Super::Exit();
}

bool UITT_SceneState_Chapter01::LoadingPostProcess(float DeltaTime)
{
	PlayerSpawnPoints.Emplace(UITT_InstUtil::GetSpawnPoint(CharacterName::Cody));
	PlayerSpawnPoints.Emplace(UITT_InstUtil::GetSpawnPoint(CharacterName::May));
	
	for(const auto& SpawnPoint : PlayerSpawnPoints)
	{
		CreatePlayer(SpawnPoint);
	}
	
	return true;
}

void UITT_SceneState_Chapter01::CreatePlayer(const TWeakObjectPtr<AITT_PlayerSpawnPoint>& _PlayerSpawnPoint)
{
	for(const auto& SpawnPoint : PlayerSpawnPoints)
	{
		if(SpawnPoint.IsValid() == false)
		{
			return;
		}
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
		Cody->ChangePlayerState(EITT_UnitState::Chapter_01);

		if(const TObjectPtr<AITT_CharacterBase> CharacterBase = Cody->GetCharacterBase())
		{
			CharacterBase->GetCharacterRootComponent()->ComponentTags.Emplace(FName("Title"));
		}

		UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(Cody));
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
		May->ChangePlayerState(EITT_UnitState::Chapter_01);

		if(const TObjectPtr<AITT_CharacterBase> CharacterBase = May->GetCharacterBase())
		{
			CharacterBase->GetCharacterRootComponent()->ComponentTags.Emplace(FName("Title"));
		}

		UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(May));
	}
}

void UITT_SceneState_Chapter01::ResetPlayer()
{
}

void UITT_SceneState_Chapter01::ChangeCamera()
{
}
