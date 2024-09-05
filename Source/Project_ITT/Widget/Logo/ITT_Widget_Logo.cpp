// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Logo.h"

#include "PROJECT_ITT/Manager/ITT_SceneManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"

void UITT_Widget_Logo::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UITT_Widget_Logo::FinishWidget()
{
	Super::FinishWidget();
}

void UITT_Widget_Logo::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
	}
	else if(AnimName == DefaultWidgetAnimation::DisAppearance)
	{
		gSceneMng.ChangeScene(EITT_GameSceneType::Title);
	}

	Super::OnAnimFinished(AnimName);
}