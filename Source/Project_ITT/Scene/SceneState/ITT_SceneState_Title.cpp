// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneState_Title.h"

#include "Animation/ITT_AnimInstance_Doll.h"
#include "Animation/ITT_AnimInstance_Rose.h"
#include "Manager/ITT_InputManager.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Actor/SpawnPoint/ITT_PlayerSpawnPoint_Rose.h"
#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "PROJECT_ITT/Manager/ITT_CameraManager.h"
#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer_Rose.h"
#include "PROJECT_ITT/Widget/Select/ITT_Widget_Select.h"
#include "Unit/ITT_BasePlayer_Doll.h"
#include "Widget/Title/ITT_Widget_Title.h"

void UITT_SceneState_Title::Begin()
{
	Super::Begin();
	SelectData = FITT_SelectData();
	
	gInputMng.GetBindSelectDelegate().AddUObject(this, &UITT_SceneState_Title::OnAxisSelect);
	gInputMng.GetBindPickDollDelegate().AddUObject(this, &UITT_SceneState_Title::OnPickDoll);
}

void UITT_SceneState_Title::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TitleWidget.IsValid())
	{
		return;
	}
	
	TitleWidget = Cast<UITT_Widget_Title>(gWidgetMng.GetWidget(UITT_Widget_Title::GetWidgetName()));
}

void UITT_SceneState_Title::Exit()
{
	gInputMng.GetBindSelectDelegate().RemoveAll(this);
	Super::Exit();
}

bool UITT_SceneState_Title::LoadingPostProcess(float DeltaTime)
{
	if(bFirst == false)
	{
		if(const TObjectPtr<UITT_Widget_Select> SelectWidget = Cast<UITT_Widget_Select>(gWidgetMng.Create_Widget(UITT_Widget_Select::GetWidgetName())))
		{
			SelectWidget->BindChangeStorySceneFunc([]()
			{
				gWidgetMng.DestroyWidget(UITT_Widget_Select::GetWidgetName());
				gWidgetMng.Create_Widget(UITT_Widget_Title::GetWidgetName());
			});
		}
		bFirst = true;
	}
	
	PlayerSpawnPoint = UITT_InstUtil::GetSpawnPoint(CharacterName::Rose);
	CreatePlayer();
	ChangeCamera();
	CreateDoll();
	
	return true;
}

void UITT_SceneState_Title::CreatePlayer()
{
	if(PlayerSpawnPoint.IsValid() == false)
	{
		return;
	}
	
	if(Player.IsValid())
	{
		ITT_LOG(TEXT("Is Already Has Player Actor. Please check this level!"));
		ResetPlayer();	
	}
	
	const TObjectPtr<UITT_BasePlayer_Rose> Rose = Cast<UITT_BasePlayer_Rose>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::Rose), UITT_BasePlayer_Rose::StaticClass(), PlayerSpawnPoint->GetActorLocation(), PlayerSpawnPoint->GetActorRotation()));
	if(Rose == nullptr)
	{
		return;
	}

	Player = Rose;
	Player->SetSelfPlayer(true);
	Player->ChangePlayerState(EITT_UnitState::Title);
	TObjectPtr<AITT_CharacterBase> CharacterBase = nullptr;
	CharacterBase = Player->GetCharacterBase();
	if(!CharacterBase)
	{
		return;
	}
	CharacterBase->GetRootComponent()->ComponentTags.Emplace(FName("Title"));
	RoseAnimInst = Cast<UITT_AnimInstance_Rose>(CharacterBase->GetAnimInstance());
	UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(Rose));
	UITT_InstUtil::OnPossessUnit(Cast<AITT_CharacterBase>(CharacterBase));
}

void UITT_SceneState_Title::ResetPlayer()
{
	if(Player.IsValid() == false)
	{
		return;
	}

	//Player->SetAutoMovement(false, nullptr);
	Player->SetActorEnableCollision(false);
	Player->ClearComponentOverlaps();
	Player->SetSelfPlayer(false);

	gUnitMng.DestroyUnit(Player->GetUnitHandle());
	Player.Reset();
}

void UITT_SceneState_Title::ChangeCamera() const
{
	gCameraMng.ChangeCamera(static_cast<uint8>(EITT_GameCameraType::Title));
}

void UITT_SceneState_Title::CreateDoll() const
{
	const TObjectPtr<UITT_BasePlayer_Doll> CodyDoll = Cast<UITT_BasePlayer_Doll>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::CodyDoll), UITT_BasePlayer_Doll::StaticClass()));
	if(CodyDoll == nullptr)
	{
		return;
	}

	const TObjectPtr<UITT_BasePlayer_Doll> MayDoll = Cast<UITT_BasePlayer_Doll>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::MayDoll), UITT_BasePlayer_Doll::StaticClass()));
	if(MayDoll == nullptr)
	{
		return;
	}

	if(Player->DoesSocketExist(SocketName::CodyAttach))
	{
		Player->AttachMeshToSocket(SocketName::CodyAttach, CodyDoll);
	}

	if(Player->DoesSocketExist(SocketName::MayAttach))
	{
		Player->AttachMeshToSocket(SocketName::MayAttach, MayDoll);
	}

	Player->SetDollAnimInst(Cast<UITT_AnimInstance_Doll>(MayDoll->GetAnimInstance()), Cast<UITT_AnimInstance_Doll>(CodyDoll->GetAnimInstance()));
}

void UITT_SceneState_Title::OnAxisSelect(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f))
	{
		return;
	}
	
	const bool bMoveRight = AxisValue > 0;
	const FITT_ResultSelectData ResultData = SelectData.SetPlayerData(ITT_Player::First, bMoveRight);
	if(ResultData.bChanged)
	{
		TitleWidget->RefreshCharacterState(ResultData.Player, ResultData.NextPosition);
		RoseAnimInst.Get()->Select(ResultData.NextPosition);
	}
}

void UITT_SceneState_Title::OnPickDoll()
{
	TitleWidget->SelectState();
}
