// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CameraState_Practice.h"

#include "Components/CapsuleComponent.h"
#include "Manager/ITT_InputManager.h"
#include "Manager/ITT_WidgetManager.h"
#include "Manager/Tool/WidgetTool/ITT_BuiltInWidgetTool.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/ITT_PlayerController.h"
#include "PROJECT_ITT/Camera/ITT_Actor_Camera.h"
#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "PROJECT_ITT/Manager/ITT_CameraManager.h"
#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/Unit/ITT_UnitBase.h"

UITT_CameraState_Practice::UITT_CameraState_Practice()
{
}

UITT_CameraState_Practice::~UITT_CameraState_Practice()
{
}

void UITT_CameraState_Practice::Initialize(uint8 Index, const FName& Name)
{
	Super::Initialize(Index, Name);

	gInputMng.GetBindAimedDelegate().AddUObject(this, &UITT_CameraState_Practice::SetAimed);
}

void UITT_CameraState_Practice::Finalize()
{
	Super::Finalize();
}

void UITT_CameraState_Practice::Begin()
{
	Super::Begin();

	// Step 01. 해당 카메라 생성 및 기본 초기화 작업
	InitCamera();
	
	// Step 02. 해당 카메라 활성화
	gCameraMng.ActiveCamera(Cody_Camera);
}

void UITT_CameraState_Practice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_CameraState_Practice::Exit()
{
	if(Cody_CameraCapsuleComponent.IsValid())
	{
		Cody_CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
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
	
	gInputMng.GetBindAimedDelegate().RemoveAll(this);
	
	Super::Exit();
}

void UITT_CameraState_Practice::InitCamera()
{
	Aim_Camera = gCameraMng.CreateCameraActor(AITT_Actor_Camera::StaticClass(), EITT_GameCameraType::Practice);

	if(Aim_Camera == nullptr)
	{
		ITT_LOG(TEXT("No camera object created. Check out the camera manager."))
		return;
	}
	
	Aim_Camera->InitialInput(TEXT("Practice_AimCamera"));
	
	// 일단 코디 카메라만 만들어두고 나중에 메이가 필요할 때 추가.
	Cody_Camera = gCameraMng.CreateCameraActor(AITT_Actor_Camera::StaticClass(), EITT_GameCameraType::Practice);

	if(Cody_Camera == nullptr)
	{
		ITT_LOG(TEXT("No camera object created. Check out the camera manager."))
		return;
	}
	
	Cody_Camera->InitialInput(TEXT("Practice_CodyCamera"));
	TArray<UActorComponent*> CapsuleComponents = Cody_Camera->GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("CameraCollision"));
	if(CapsuleComponents.Num() > 0)
	{
		Cody_CameraCapsuleComponent = Cast<UCapsuleComponent>(CapsuleComponents[0]);

		if(Cody_CameraCapsuleComponent.IsValid())
		{
			Cody_CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		}
	}
	
	if(const TObjectPtr<UITT_UnitBase> PlayerUnit = gUnitMng.GetUnitTableId(ITT_Character::Cody))
	{
		ActorTickEvent = PlayerUnit->OnActorTickDelegate.AddUObject(this, &UITT_CameraState_Practice::ActorTickFunc);
		IsValid(PlayerUnit);
	}
}

void UITT_CameraState_Practice::ActorTickFunc(TObjectPtr<UITT_UnitBase> Unit)
{
	if(Unit == nullptr)
	{
		return;
	}

	const TObjectPtr<AITT_CharacterBase> Character = Unit->GetCharacterBase();

	if(Character == nullptr)
	{
		return;
	}

	if(bAimed == false)
	{
		Cody_Camera->SetCameraAspectRatio(UITT_InstUtil::GetAspectRatio());
		Cody_Camera->SetFieldOfView(80.f);
		Cody_Camera->SetSpringOffset(FVector(0.f, 0.f, 140.f));
		Cody_Camera->SetCameraDistance(FVector(0.f, 0.f, 140.f).Size());
		Cody_Camera->SetTargetRotator(FRotator(0.f, 0.f, 0.f));

		// Camera Step - 카메라의 위치 "UnitVector" 은 계속 따라다녀야하는데, 유닛의 방향은 알 필요가 없다. 하지만 최초 캐릭터와 카메라는 같은 방향을 바라보아야하기 때문에 딱 한번 맞춰주어야함
		Cody_Camera->SetTargetPosition(Character->GetCurrentLocation());	
	}
	else
	{
		Aim_Camera->SetCameraAspectRatio(UITT_InstUtil::GetAspectRatio());
		Aim_Camera->SetFieldOfView(80.f);
		Cody_Camera->SetSpringOffset(FVector(0.f, 0.f, 140.f));
		Cody_Camera->SetCameraDistance(FVector(0.f, 0.f, 140.f).Size());
		Aim_Camera->SetCameraRelativeLocation(FVector(-300.f, 100.f, 50.f));
		Aim_Camera->SetCameraRelativeRotation(FRotator(0.f, 0.f, 0.f));
		Aim_Camera->SetTargetRotator(FRotator(0.f, 0.f, 0.f));
		
		Aim_Camera->SetTargetPosition(Character->GetCurrentLocation());
	}
}

void UITT_CameraState_Practice::SetAimed()
{
	if(bAimed == false)
	{
		gCameraMng.ActiveCamera(Aim_Camera, 0.2f);
		bAimed = true;
	}
	else
	{
		gCameraMng.ActiveCamera(Cody_Camera, 0.2f);
		bAimed = false;
	}
}
