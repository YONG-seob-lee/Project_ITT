// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Button.h"

#include "Framework/Application/NavigationConfig.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "PROJECT_ITT/ITT_InstUtil.h"

UITT_Button::UITT_Button()
{
}

UITT_Button::~UITT_Button()
{
}

void UITT_Button::NativeConstruct()
{
	Super::NativeConstruct();
}

void UITT_Button::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
}

const FText UITT_Button::GetPaletteCategory()
{
	return FText::FromString("ITT Custom");
}

void UITT_Button::OnHoverJoyStick()
{
	HandleFocusReceived();
	//NativeOnHovered();
}

void UITT_Button::UnHoverJoyStick()
{
	NativeOnUnhovered();
}

void UITT_Button::SetDelegates()
{
	OnClicked().AddUObject(this, &UITT_Button::OnClick);
	OnPressed().AddUObject(this, &UITT_Button::OnPress);
	OnReleased().AddUObject(this, &UITT_Button::OnRelease);
	OnHovered().AddUObject(this, &UITT_Button::OnHover);
	OnUnhovered().AddUObject(this, &UITT_Button::OnUnhover);
}

void UITT_Button::OnClick()
{
	if (IsUseClockedDelay())
	{
		const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
		if (!World)
		{
			ITT_CHECK(false);
			ITT_LOG(TEXT("Wrong Process Please Check ITT_Button Class"))
				return;
		}

		const float CurrentClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
		if (LastClickedTime + ClickedDelayTime >= CurrentClickedTime)
		{
			ITT_OnClickedInDelayTimeDelegate.Broadcast();
			return;
		}
		LastClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
	}

	if (IsUseLongPressedEvent() == false)
	{
		ITT_OnClickedDelegate.Broadcast();
	}
}

void UITT_Button::OnPress()
{
	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UITT_InstUtil::GetGameWorld()->GetTimerManager();
		TimerManager.SetTimer(PressTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			ITT_OnLongPressedDelegate.Broadcast();
		}), LongPressedTime, false);
	}
	ITT_OnPressedDelegate.Broadcast();
}

void UITT_Button::OnRelease()
{
	ITT_OnReleasedDelegate.Broadcast();

	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UITT_InstUtil::GetGameWorld()->GetTimerManager();
		if(TimerManager.IsTimerActive(PressTimerHandle))
		{
			TimerManager.ClearTimer(PressTimerHandle);
		}
	}
}

void UITT_Button::OnHover()
{
	ITT_OnHoveredDelegate.Broadcast();
}

void UITT_Button::OnUnhover()
{
	ITT_OnUnhoveredDelegate.Broadcast();
}
