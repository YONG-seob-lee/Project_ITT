// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Loading.h"

namespace LoadingAnim
{
	const FName PlayLoading = TEXT("PlayLoading");

	constexpr int32 MaxState = 2;
}

void UITT_Widget_Loading::SetLoadingData(EITT_LoadingPageType _LoadingPage)
{
}

void UITT_Widget_Loading::ShowLoading()
{
	CurrentImageState = 0;
	PlayAnimationByName(LoadingAnim::PlayLoading);
}

void UITT_Widget_Loading::OnAnimFinished(const FName& AnimName)
{
	Super::OnAnimFinished(AnimName);

	if(AnimName == LoadingAnim::PlayLoading)
	{
		if(CurrentImageState == LoadingAnim::MaxState)
		{
			CurrentImageState = 0;
		}
		else
		{
			CurrentImageState++;
		}

		PlayAnimationByName(AnimName);
	}
}
