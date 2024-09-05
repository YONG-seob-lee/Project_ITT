// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Logo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Logo : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Logo"); }
	
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;
	
protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
};
