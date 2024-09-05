// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CameraState_CharacterSpringArm.h"

#include "ITT_InstUtil.h"
#include "ITT_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Character/ITT_CharacterBase.h"
#include "GameFramework/GameSession.h"
#include "Manager/ITT_CameraManager.h"
#include "Manager/ITT_UnitManager.h"
#include "Unit/ITT_UnitBase.h"

UITT_CameraState_CharacterSpringArm::UITT_CameraState_CharacterSpringArm()
{
}

UITT_CameraState_CharacterSpringArm::~UITT_CameraState_CharacterSpringArm()
{
}

void UITT_CameraState_CharacterSpringArm::Initialize(uint8 Index, const FName& Name)
{
	Super::Initialize(Index, Name);
}

void UITT_CameraState_CharacterSpringArm::Finalize()
{
	Super::Finalize();
}

void UITT_CameraState_CharacterSpringArm::Begin()
{
	Super::Begin();

	// Step 01. 해당 카메라 생성 및 기본 초기화 작업
	InitCamera();
	
	// Step 02. 해당 카메라 활성화
	//gCameraMng.ActiveCamera(EITT_GameCameraType::Practice);
	if (Cody_Camera)
	{
		Cody_Camera->Activate(true);
	}
}

void UITT_CameraState_CharacterSpringArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_CameraState_CharacterSpringArm::Exit()
{
	Super::Exit();
	
	const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(UITT_InstUtil::GetPlayerController());
	if(PlayerController != nullptr)
	{
		return;
	}
	
	if(const TObjectPtr<UITT_UnitBase> UnitBase = gUnitMng.GetUnit(PlayerController->GetUnitHandle()))
	{
		UnitBase->OnActorTickDelegate.Remove(ActorTickEvent);
	}

	PlayerController->ResetUnitHandle();
	ActorTickEvent.Reset();
}

void UITT_CameraState_CharacterSpringArm::InitCamera()
{
	Super::InitCamera();

	if (!GetWorld() || !GetWorld()->GetFirstPlayerController())
	{
		return;
	}
	
	CharacterBase = Cast<AITT_CharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (CharacterBase != nullptr)
	{
		Cody_Camera = CharacterBase->GetFollowCamera();
		if(Cody_Camera == nullptr)
		{
			ITT_LOG(TEXT("No camera object."))
			return;
		}
	}

	if(const TObjectPtr<UITT_UnitBase> PlayerUnit = gUnitMng.GetCurrentUnit())
	{
		ActorTickEvent = PlayerUnit->OnActorTickDelegate.AddUObject(this, &UITT_CameraState_CharacterSpringArm::ActorTickFunc);
		IsValid(PlayerUnit);
	}
}

void UITT_CameraState_CharacterSpringArm::ActorTickFunc(TObjectPtr<UITT_UnitBase> Unit)
{
}
