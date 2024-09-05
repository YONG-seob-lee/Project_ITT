// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_DialogScreenFader.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_DialogScreenFader : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/Widgets/Fade/DialogScreenFader.DialogScreenFader")); }
	
	void StartScreenFade(bool bFadeOut, const TFunction<void()>& FadeCallback = nullptr);
	
protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
	
private:
	void FinishedFadeIn();
	void FinishedFadeOut();
	
	TFunction<void()> FadeInCompleteCallback;
	TFunction<void()> FadeOutCompleteCallback;
};
