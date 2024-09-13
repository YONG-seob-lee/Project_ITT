// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CameraManager.h"

#include "ITT_TableManager.h"
#include "Camera/State/ITT_CameraState_CharacterSpringArm.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Camera/ITT_Actor_Camera.h"
#include "PROJECT_ITT/Camera/State/ITT_CameraState_Chapter01.h"
#include "PROJECT_ITT/Camera/State/ITT_CameraState_Chapter02.h"
#include "PROJECT_ITT/Camera/State/ITT_CameraState_Practice.h"
#include "PROJECT_ITT/Camera/State/ITT_CameraState_Title.h"
#include "PROJECT_ITT/StateMachine/ITT_StateMachine.h"

void UITT_CameraManager::BuiltInInitialize()
{
	if(CameraStateMachine)
	{
		return;
	}
	
	CameraStateMachine = ITT_NewObject<UITT_StateMachine>(this, UITT_StateMachine::StaticClass());
	CameraStateMachine->Create();
	CameraStateMachine->AddToRoot();
}

void UITT_CameraManager::Initialize()
{
	UITT_Singleton<UITT_CameraManager>::Initialize();
}

void UITT_CameraManager::Finalize()
{
	CameraActors.Empty();
}

void UITT_CameraManager::BuiltInFinalize()
{
	if(CameraStateMachine)
	{
		CameraStateMachine->Destroy();
		CameraStateMachine->RemoveFromRoot();
		CameraStateMachine = nullptr;
	}	
}

void UITT_CameraManager::Tick(float _DeltaTime)
{
	if(CameraStateMachine)
	{
		CameraStateMachine->Tick(_DeltaTime);
	}
}

void UITT_CameraManager::RegisterCameras()
{
	// 카메라 등록
	RegistCameraState(static_cast<uint8>(EITT_GameCameraType::Title), TEXT("Title"), UITT_CameraState_Title::StaticClass());
	RegistCameraState(static_cast<uint8>(EITT_GameCameraType::Chapter_01), TEXT("Chapter_01"), UITT_CameraState_Chapter01::StaticClass());
	RegistCameraState(static_cast<uint8>(EITT_GameCameraType::Chapter_02), TEXT("Chapter_02"), UITT_CameraState_Chapter02::StaticClass());
	RegistCameraState(static_cast<uint8>(EITT_GameCameraType::Practice), TEXT("Practice"), UITT_CameraState_Practice::StaticClass());
}

void UITT_CameraManager::ChangeCameraState(uint8 Index, bool bInstant)
{
	CameraActors.Empty();
	
	if(CameraStateMachine)
	{
		CameraStateMachine->SetState(Index, bInstant);
	}
}

TObjectPtr<AITT_Actor_Camera> UITT_CameraManager::CreateCameraActor(const TSubclassOf<AITT_Actor_Camera>& CameraActorType, EITT_GameCameraType _CameraType)
{
	const FString CameraType = UITT_InstUtil::ConvertEnumToString<EITT_GameCameraType>("EITT_GameCameraType", _CameraType);

	const TObjectPtr<AITT_Actor_Camera> CameraActor = Cast<AITT_Actor_Camera>(UITT_InstUtil::SpawnActor(CameraActorType, FVector::ZeroVector, FRotator::ZeroRotator, CameraType, ESpawnActorCollisionHandlingMethod::AlwaysSpawn, true));
	if(CameraActor == nullptr)
	{
		return {};
	}
#if WITH_EDITOR
	CameraActor->SetActorLabel(CameraActor->GetName());
#endif
	CameraActor->SetCameraType(_CameraType);
	
	AddCameraActor(CameraActor);
	
	return CameraActor;
}

bool UITT_CameraManager::ActiveCamera(const TObjectPtr<AITT_Actor_Camera>& _ActiveCamera, float BlendTime) const
{
	if(!CameraActors.Contains(_ActiveCamera))
	{
		return false; 
	}
	
	for(const auto& Camera : CameraActors)
	{
		if(Camera.Get()->IsActivate() == false)
		{
			Camera.Get()->Deactive();
		}
	}
	
	_ActiveCamera->Active(BlendTime);

	return true;
}

TObjectPtr<AITT_Actor_Camera> UITT_CameraManager::GetActiveCamera()
{
	for(const auto& Camera : CameraActors)
	{
		if(Camera.Get()->IsActivate())
		{
			return Camera;
		}
	}
	
	return nullptr;
}

void UITT_CameraManager::RegistCameraState(uint8 Index, const FName& Name, const TSubclassOf<UITT_StateBase>& SceneType)
{
	if(CameraStateMachine)
	{
		CameraStateMachine->RegistState(Index, Name, SceneType);
	}
}

void UITT_CameraManager::AddCameraActor(TObjectPtr<AITT_Actor_Camera> CameraActor)
{
	CameraActors.Emplace(CameraActor);
}
