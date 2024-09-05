// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BuiltInWidgetTool.h"

#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Widget/Fade/ITT_Widget_DialogScreenFader.h"
#include "PROJECT_ITT/Widget/Fade/ITT_Widget_Toast.h"

void UITT_BuiltInWidgetTool::BuiltInitialize()
{
	PreTouchProcessor = MakeShareable(new FITT_PreTouchProcessor());
	FSlateApplication::Get().RegisterInputPreProcessor(PreTouchProcessor);
	PreTouchProcessor->Initialize();
	
	DialogScreenFader = Cast<UITT_Widget_DialogScreenFader>(gWidgetMng.Create_Widget_NotManaging(UITT_Widget_DialogScreenFader::GetWidgetPath()));
	if(DialogScreenFader)
	{
		DialogScreenFader->FillDefaultAnimations();
		DialogScreenFader->AddToViewport(500);
		DialogScreenFader->SetVisibility(ESlateVisibility::Collapsed);

		gWidgetMng.Test(DialogScreenFader);
	}

	ToastWidget = Cast<UITT_Widget_Toast>(gWidgetMng.Create_Widget_NotManaging(UITT_Widget_Toast::GetWidgetPath()));
	if(ToastWidget)
	{
		ToastWidget->FillDefaultAnimations();
		ToastWidget->AddToViewport(1000);
		ToastWidget->SetZOrder(1000);
		ToastWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UITT_BuiltInWidgetTool::Initialize()
{
}

void UITT_BuiltInWidgetTool::Finalize()
{
	PreTouchProcessor->Finalize();
	FSlateApplication::Get().UnregisterInputPreProcessor(PreTouchProcessor);
}

void UITT_BuiltInWidgetTool::Tick(float DeltaTime)
{
}

void UITT_BuiltInWidgetTool::UpdatePreTouchProcessor() const
{
	if(PreTouchProcessor == nullptr)
	{
		return;
	}

	PreTouchProcessor->UpdateTouchWidget();
}
