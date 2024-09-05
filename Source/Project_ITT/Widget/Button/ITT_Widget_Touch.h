// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Touch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Touch : public UITT_Widget
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;
	
	void RebuildTouchWidget() const;
	
	void PlayTouch() const;

private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNiagaraSystemWidget> CPP_TouchEffectWidget = nullptr;
};
