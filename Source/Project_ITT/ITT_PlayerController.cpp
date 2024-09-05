// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_PlayerController.h"

#include "GameFramework/InputSettings.h"
#include "Manager/Tool/InputTouch/ITT_TouchInterface.h"
#include "Manager/Tool/InputTouch/ITT_VirtualJoyStick.h"
#include "Slate/DeferredCleanupSlateBrush.h"

AITT_PlayerController::AITT_PlayerController()
{
	SetShowMouseCursor(true);
}

AITT_PlayerController::~AITT_PlayerController()
{
}

void AITT_PlayerController::CreateTouchInterface()
{
	const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(Player);

	if(IsValid(LocalPlayer) == false)
	{
		return;
	}

	if(IsValid(LocalPlayer->ViewportClient) && SITT_VirtualJoyStick::ShouldDisplayTouchInterface())
	{
		if(VirtualJoystick.IsValid())
		{
			Cast<ULocalPlayer>(Player)->ViewportClient->RemoveViewportWidgetContent(VirtualJoystick.ToSharedRef());
		}

		if(CurrentTouchInterface == nullptr)
		{
			const FSoftObjectPath& DefaultTouchInterfaceName = GetDefault<UInputSettings>()->DefaultTouchInterface;

			if(DefaultTouchInterfaceName.IsValid())
			{
				const FSoftClassPath& ClassPath = FSoftClassPath(*DefaultTouchInterfaceName.ToString());
				if(ClassPath.IsValid())
				{
					if(const TObjectPtr<UClass> TouchInterfaceClass = Cast<UClass>(ClassPath.TryLoad()))
					{
						CurrentTouchInterface = ITT_NewObject<UITT_TouchInterface>(this, TouchInterfaceClass);
					}
				}
			}
		}

		if(CurrentTouchInterface)
		{
			// 조이스틱 생성
			VirtualJoystick = SNew(SITT_VirtualJoyStick);

			// 플레이어 뷰포트에 때려넣음
			LocalPlayer->ViewportClient->AddViewportWidgetContent(VirtualJoystick.ToSharedRef());

			ActivateTouchInterface(CurrentTouchInterface);
		}
	}
}

void AITT_PlayerController::ActivateTouchInterface(UTouchInterface* NewTouchInterface)
{
	if(NewTouchInterface)
	{
		if(VirtualJoystick.IsValid())
		{
			if(SITT_VirtualJoyStick* ITT_VirtualJoyStick = static_cast<SITT_VirtualJoyStick*>(VirtualJoystick.Get()))
			{
				if(const TObjectPtr<UITT_TouchInterface> TouchInterface = Cast<UITT_TouchInterface>(NewTouchInterface))
				{
					ITT_VirtualJoyStick->ImageCenter = TouchInterface->ImageCenter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageCenter)) : TSharedPtr<ISlateBrushSource>();
					ITT_VirtualJoyStick->CenterImageSize = TouchInterface->CenterImageSize;
					ITT_VirtualJoyStick->CenterImageOpacity = TouchInterface->CenterImageOpacity;
					ITT_VirtualJoyStick->ImageOuter = TouchInterface->ImageOuter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageOuter)) : TSharedPtr<ISlateBrushSource>();
					ITT_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					ITT_VirtualJoyStick->OuterImageOpacity = TouchInterface->OuterImageOpacity;
					ITT_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					ITT_VirtualJoyStick->Center = TouchInterface->Controls[0].Center;
					ITT_VirtualJoyStick->ThumbSize = TouchInterface->Controls[0].ThumbSize;
					ITT_VirtualJoyStick->InteractionSize = TouchInterface->Controls[0].InteractionSize;
					ITT_VirtualJoyStick->InputScale = TouchInterface->Controls[0].InputScale;
				}
			}
		}
	}
	
	Super::ActivateTouchInterface(NewTouchInterface);
}

SITT_VirtualJoyStick* AITT_PlayerController::GetVirtualJoyStick() const
{
	if(SVirtualJoystick* JoyStick = VirtualJoystick.Get())
	{
		return static_cast<SITT_VirtualJoyStick*>(JoyStick);
	}
	
	return nullptr;
}

void AITT_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
