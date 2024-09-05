// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_State_SelectPick.h"

#include "ITT_State_PlayerNormal.h"
#include "PROJECT_ITT/Manager/ITT_InputManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer.h"
#include "PROJECT_ITT/Widget/Title/ITT_Widget_Title.h"

void UITT_State_SelectPick::Begin()
{
	OwnerUnit = CastChecked<UITT_BasePlayer>(GetOuter());
	if(OwnerUnit == nullptr)
	{
		return;
	}
	
	gInputMng.RegistSelectCharacterButton(FSimpleDelegate::CreateUObject(this, &UITT_State_SelectPick::SelectCharacter));

	TitleWidget = Cast<UITT_Widget_Title>(gWidgetMng.GetWidget(UITT_Widget_Title::GetWidgetName()));

	if(TitleWidget.IsValid() == false)
	{
		ITT_LOG(TEXT("Title widget is not valid! Please check Widget Instance or Table"));
	}
}

void UITT_State_SelectPick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_State_SelectPick::Exit()
{
	Super::Exit();
}

void UITT_State_SelectPick::SelectCharacter()
{
	if(TitleWidget.IsValid() == false)
	{
		return;
	}
	
	if(bAnySelected == false)
	{
		TitleWidget->SelectState(true, false);
	}
	else
	{
		TitleWidget->SelectState(true, true);
	}
	
}
