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
}

void UITT_CameraState_Practice::Finalize()
{
	Super::Finalize();
}

void UITT_CameraState_Practice::Begin()
{
	Super::Begin();
}

void UITT_CameraState_Practice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_CameraState_Practice::Exit()
{	
	Super::Exit();
}