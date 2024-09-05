// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneState_Logo.h"

#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Widget/Logo/ITT_Widget_Logo.h"

void UITT_SceneState_Logo::Begin()
{
	Super::Begin();

	gWidgetMng.Create_Widget(UITT_Widget_Logo::GetWidgetName());
}

void UITT_SceneState_Logo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_SceneState_Logo::Exit()
{
	gWidgetMng.DestroyWidget(UITT_Widget_Logo::GetWidgetName());
	Super::Exit();
}
