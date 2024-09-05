// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_DialogScreenFader.h"

#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Widget/Select/ITT_Widget_Select.h"

namespace FadeType
{
	const FName FadeOut = TEXT("FadeOut");
	const FName FadeIn = TEXT("FadeIn");
	const FName Loop = TEXT("Loop");
}

void UITT_Widget_DialogScreenFader::StartScreenFade(bool bFadeOut, const TFunction<void()>& FadeCallback)
{
	FadeInCompleteCallback = nullptr;
	FadeOutCompleteCallback = nullptr;

	if(bFadeOut)
	{
		FadeOutCompleteCallback = FadeCallback;
	}
	else
	{
		FadeInCompleteCallback = FadeCallback;
	}
	SetVisibility(ESlateVisibility::Visible);

	if(bFadeOut)
	{
		PlayAnimationByName(FadeType::FadeOut);
	}
	else
	{
		PlayAnimationByName(FadeType::FadeIn);
	}
}

void UITT_Widget_DialogScreenFader::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == FadeType::FadeOut)
	{
		FinishedFadeOut();
	}
	else if(AnimName == FadeType::FadeIn)
	{
		FinishedFadeIn();
	}
	else if(AnimName == FadeType::Loop)
	{
		if(FadeOutCompleteCallback)
		{
			FadeOutCompleteCallback();
		}
		PlayAnimationByName(FadeType::FadeIn);
	}
}

void UITT_Widget_DialogScreenFader::FinishedFadeIn()
{
	if(FadeInCompleteCallback)
	{
		FadeInCompleteCallback();
	}
	ITT_LOG(TEXT("FadeIn Finished"));
	SetVisibility(ESlateVisibility::Collapsed);
}

void UITT_Widget_DialogScreenFader::FinishedFadeOut()
{
	ITT_LOG(TEXT("FadeOut Finished"));

	PlayAnimationByName(FadeType::Loop, 0.f, 4);
}
