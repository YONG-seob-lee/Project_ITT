// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_FadeTool.h"

#include "PROJECT_ITT/Manager/ITT_TableManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Manager/Tool/WidgetTool/ITT_BuiltInWidgetTool.h"
#include "PROJECT_ITT/Widget/Fade/ITT_Widget_DialogScreenFader.h"
#include "PROJECT_ITT/Widget/Fade/ITT_Widget_Loading.h"

namespace CommonData
{
	constexpr float Load_Min_Time = 3.f;
}
void UITT_FadeTool::Initialize()
{
	DialogScreenFader = gWidgetMng.GetBuiltInWidgetTool()->GetDialogScreenFader();
	
	LoadingMinimumTime = CommonData::Load_Min_Time;
}

void UITT_FadeTool::Request(UITT_FadeCommand* Command)
{
	Commands.Emplace(Command);
	
	if(CurrentStep == EITT_FadeStep::Ready)
	{
		StartFadeOut();
	}
}

void UITT_FadeTool::FinishRequest()
{
	CurrentStep = EITT_FadeStep::Ready;
	bLoadStart = false;
	bLoadComplete = false;
	LoadingMinimumTime = 0.f;
	LoadElapsedTime = 0.f;

	const int32 CommandsNum = Commands.Num();
	for(int32 i = 0 ; i < CommandsNum; i++)
	{
		Commands[0]->RemoveFromRoot();
		ITT_DeleteObject(Commands[0]);
		Commands.RemoveAt(0);
	}
}

void UITT_FadeTool::Tick(float DeltaTime)
{
	if(bLoadComplete)
	{
		if(CurrentStep == EITT_FadeStep::ExitFadeOut)
		{
			CurrentStep = EITT_FadeStep::EnterFadeIn;
			StartFadeIn();
			return;
		}
	}
	else
	{
		if(bLoadStart)
		{
			LoadElapsedTime += DeltaTime;
			for(int32 i = 0 ; i < Commands.Num() ; ++i)
			{
				const TObjectPtr<UITT_FadeCommand> Command = Commands[i];
				if(Command->OnFadeOutComplete.IsBound())
				{
					Command->OnFadeOutComplete.Execute();
					Command->OnFadeOutComplete.Unbind();
				}
				if(Command->OnCheckLoadComplete.IsBound())
				{
					if(Command->OnCheckLoadComplete.Execute() == false)
					{
						return;
					}
				}

				if(Command->GetLoadingPageType() != EITT_LoadingPageType::None)
				{
					if(LoadingMinimumTime <= LoadElapsedTime)
					{
						bLoadComplete = true;
					}
				}
				else
				{
					bLoadComplete = true;
				}
			}
		}	
	}
}

void UITT_FadeTool::StartFadeOut()
{
	if(Commands.Num() <= 0)
	{
		return;
	}

	for(int32 i = 0 ; i < Commands.Num() ; ++i)
	{
		const TObjectPtr<UITT_FadeCommand> Command = Commands[i].Get();
		if(Command->GetFadeType() != EITT_FadeStyle::None)
		{
			FadeWidgetCommand = Command;
			break;
		}
	}

	if(FadeWidgetCommand == nullptr)
	{
		return;
	}

	CurrentStep = EITT_FadeStep::EnterFadeOut;

	PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), true, FadeWidgetCommand->GetIsDirectFadeOut());
}

void UITT_FadeTool::StartFadeIn()
{
	for(const TObjectPtr<UITT_FadeCommand> Command : Commands)
	{
		if(Command->OnFadeInStart.IsBound())
		{
			Command->OnFadeInStart.Execute();
		}
	}

	if(FadeWidgetCommand)
	{
		PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false , false);
	}
}

void UITT_FadeTool::PlayFadeAnimation(EITT_FadeStyle FadeType, bool bFadeOut, bool bDirectFadeIn)
{
	if(DialogScreenFader == nullptr)
	{
		return;
	}

	DialogScreenFader->Active(true);
		
	if(bFadeOut)
	{
		DialogScreenFader->StartScreenFade(true,[this](){ OnWidgetFadeOutFinished();});	
	}
	else
	{
		DialogScreenFader->StartScreenFade(false,[this](){ OnWidgetFadeInFinished();});
	}
}

void UITT_FadeTool::OnWidgetFadeOutFinished()
{
	if(CurrentStep == EITT_FadeStep::EnterFadeOut)
	{
		CurrentStep = EITT_FadeStep::ExitFadeOut;
		if(!FadeWidgetCommand)
		{
			return;
		}
		
		if(FadeWidgetCommand->GetFadeType() == EITT_FadeStyle::Dialog)
		{
			if(FadeWidgetCommand->GetLoadingPageType() != EITT_LoadingPageType::None)
			{
				const TObjectPtr<UITT_Widget_Loading> LoadingWidget = gWidgetMng.GetBuiltInWidgetTool()->GetLoadingWidget();
				if(LoadingWidget == nullptr)
				{
					return;
				}
				LoadingWidget->SetLoadingData(FadeWidgetCommand->GetLoadingPageType());
				LoadingWidget->ShowLoading();

				//PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false, false);
			}
			else
			{
				bLoadStart = true;
			}	
		}
	}
}

void UITT_FadeTool::OnWidgetFadeInFinished()
{
	if(CurrentStep == EITT_FadeStep::EnterFadeIn)
	{
		CurrentStep = EITT_FadeStep::ExitFadeIn;
		for(const TObjectPtr<UITT_FadeCommand> Command : Commands)
		{
			if(Command->OnFadeInComplete.IsBound())
			{
				Command->OnFadeInComplete.Execute();
			}
		}

		FinishRequest();
	}
}
