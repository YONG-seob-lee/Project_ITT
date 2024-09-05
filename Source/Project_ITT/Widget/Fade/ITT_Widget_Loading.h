// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Loading.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Loading : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("")); }
	
	void SetLoadingData(EITT_LoadingPageType _LoadingPage);
	void ShowLoading();

protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
	
private:
	int32 CurrentImageState = 0;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> CPP_WidgetSwitcher = nullptr;
};
