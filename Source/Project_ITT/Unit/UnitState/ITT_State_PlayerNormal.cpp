// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_State_PlayerNormal.h"

#include "PROJECT_ITT/Camera/ITT_Actor_Camera.h"
#include "PROJECT_ITT/Manager/ITT_CameraManager.h"
#include "PROJECT_ITT/Manager/ITT_InputManager.h"
#include "PROJECT_ITT/Table/Resource_Unit.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer.h"

void UITT_State_PlayerNormal::Begin()
{
	OwnerUnit = CastChecked<UITT_BasePlayer>(GetOuter());
	if(OwnerUnit == nullptr)
	{
		return;
	}
	//CameraActor = gCameraMng.GetCurrentActiveCameraActor();

	WalkSpeed = OwnerUnit->GetResourceUnitData()->WalkSpeed;
	RunSpeed = OwnerUnit->GetResourceUnitData()->RunSpeed;
	SprintSpeed = OwnerUnit->GetResourceUnitData()->SprintSpeed;

	// Bind Axis Key ( WASD , ULDR )
	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &UITT_State_PlayerNormal::OnAxisUpDown);
	gInputMng.RegistAxis(EITT_Axis_Type::Left, EITT_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &UITT_State_PlayerNormal::OnAxisLeftRight);
	gInputMng.RegistAxis(EITT_Axis_Type::Left, EITT_Action_Type::ActionLeftRight, LeftRightDelegate);

	// Bind ActionThing ( F key : Interaction , M key : WorldMap )
	gInputMng.RegistInteractionButton(FSimpleDelegate::CreateUObject(this, &UITT_State_PlayerNormal::OnClickInteraction));
}

void UITT_State_PlayerNormal::Tick(float DeltaTime)
{
	if(CameraActor == nullptr)
	{
		//CameraActor = gCameraMng.GetCurrentActiveCameraActor();
	}
	
	if(OwnerUnit)
	{
		PlayerMove();
		//InteractionProcess();
	}
}

void UITT_State_PlayerNormal::Exit()
{
	Super::Exit();
}

void UITT_State_PlayerNormal::PlayerMove()
{
	const TObjectPtr<AITT_CharacterBase> Character = OwnerUnit->GetCharacterBase();
	if(Character == nullptr)
	{
		return;
	}

	const float DetectJoyStickValue = JoyStickDistance.Size();

	// Step 1. 카메라의 정면벡터가 캐릭터의 정면벡터가 될 수 있게 캐싱
	if(CameraActor == nullptr)
	{
		return;
	}
		
	if(CachedUnitForward == FVector::ZeroVector || CachedUnitRight == FVector::ZeroVector)
	{
		CachedUnitForward = CameraActor->GetForward();
		CachedUnitRight= CameraActor->GetCross();
	}
	
	// Step 2. 캐릭터 정면벡터와 조이스틱을 바인딩
	if(DetectJoyStickValue > 0.001f)
	{
		if(JoyStickDistance.Y != 0)
		{
			CachedUnitForward = CameraActor->GetForward();
			CachedUnitRight = CameraActor->GetCross();
		}
		
		FVector NewMoveDirection = JoyStickDistance.Y * CachedUnitForward + JoyStickDistance.X * CachedUnitRight;
		ITT_LOG(TEXT("%f"), NewMoveDirection.Size());
		NewMoveDirection.Z = 0.f;
		
		// 시계, 반시계
		
		NewMoveDirection.Normalize();
		
		OwnerUnit->SetMoveSpeed(DetectJoyStickValue <= 0.5f ? WalkSpeed : RunSpeed);
		Character->MoveDirection(NewMoveDirection);
	}
	// Step 3. 캐릭터가 더이상 움직이지 않으면 캐싱데이터 제거 및 캐릭터 속도 0 ( 나중에 속도 감쇠 기능 추가해야할 듯 싶음 - 캐릭터 방향성 래깅도 필요해보임)
	else
	{
		CachedUnitForward = FVector::ZeroVector;
		CachedUnitRight = FVector::ZeroVector;
		OwnerUnit->SetMoveSpeed(0.f);
	}
	JoyStickDistance = FVector2d::ZeroVector;
}

void UITT_State_PlayerNormal::InteractionProcess()
{
}

void UITT_State_PlayerNormal::OnAxisUpDown(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.Y = AxisValue;
	}
}

void UITT_State_PlayerNormal::OnAxisLeftRight(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.X = AxisValue;
	}
}

void UITT_State_PlayerNormal::OnClickInteraction()
{
	if(OnInteractionCallback)
	{
		OnInteractionCallback();
	}
}