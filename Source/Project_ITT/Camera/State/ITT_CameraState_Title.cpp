// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CameraState_Title.h"

#include "Components/CapsuleComponent.h"
#include "Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/ITT_PlayerController.h"
#include "PROJECT_ITT/Camera/ITT_Actor_Camera.h"
#include "PROJECT_ITT/Manager/ITT_CameraManager.h"
#include "Unit/ITT_UnitBase.h"

UITT_CameraState_Title::UITT_CameraState_Title()
{
}

UITT_CameraState_Title::~UITT_CameraState_Title()
{
}

void UITT_CameraState_Title::Initialize(uint8 Index, const FName& Name)
{
	Super::Initialize(Index, Name);
}

void UITT_CameraState_Title::Finalize()
{
	Super::Finalize();
}

void UITT_CameraState_Title::Begin()
{
	Super::Begin();
	
	InitCamera();

	if(gCameraMng.ActiveCamera(CharacterSelectCamera))
	{
		BeginCameraIdle();
	}
}

void UITT_CameraState_Title::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIdleCamera)
	{
		//CharacterSelectCamera->
	}
}

void UITT_CameraState_Title::Exit()
{
	if(CameraCapsuleComponent.IsValid())
	{
		CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(UITT_InstUtil::GetPlayerController());
	if(PlayerController != nullptr)
	{
		return;
	}
	
	//PlayerController->ResetUnitHandle();
}

void UITT_CameraState_Title::InitCamera()
{
	CharacterSelectCamera = gCameraMng.CreateCameraActor(AITT_Actor_Camera::StaticClass(), EITT_GameCameraType::Title);
	CharacterSelectCamera->InitialInput(TEXT("CharacterSelectCamera"));

	if(CharacterSelectCamera != nullptr)
	{
		TArray<UActorComponent*> CapsuleComponents = CharacterSelectCamera->GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("CameraCollision"));
		if(CapsuleComponents.Num() > 0)
		{
			CameraCapsuleComponent = Cast<UCapsuleComponent>(CapsuleComponents[0]);

			if(CameraCapsuleComponent.IsValid())
			{
				CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			}
		}
	}

	if(const TObjectPtr<UITT_UnitBase> PlayerUnit = gUnitMng.GetCurrentUnit())
	{
		const TObjectPtr<AITT_CharacterBase> Character = PlayerUnit->GetCharacterBase();
		CharacterSelectCamera->SetCameraAspectRatio(UITT_InstUtil::GetAspectRatio());
		CharacterSelectCamera->SetFieldOfView(80.f);
		// CharacterSelectCamera->SetSpringOffset(FVector(0.f, 0.f, 140.f));
		// CharacterSelectCamera->SetCameraDistance(FVector(0.f, 0.f, 140.f).Size());
		CharacterSelectCamera->SetRotateNative();
		CharacterSelectCamera->SetCameraRelativeLocation(FVector(0.f, 0.f, 0.f));
		CharacterSelectCamera->SetTargetRotator(FRotator(0.f, 0.f, 0.f));
		CharacterSelectCamera->SetTargetPosition(Character->GetCurrentLocation());
	}
}

void UITT_CameraState_Title::BeginCameraIdle()
{
	
}
