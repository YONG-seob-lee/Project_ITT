// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Touch.h"
#include "NiagaraSystemWidget.h"

void UITT_Widget_Touch::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
	
	RebuildTouchWidget();
}

void UITT_Widget_Touch::FinishWidget()
{
	Super::FinishWidget();
}

void UITT_Widget_Touch::RebuildTouchWidget() const
{
	if(CPP_TouchEffectWidget)
	{
		CPP_TouchEffectWidget->RebuildWidget();
	}
}

void UITT_Widget_Touch::PlayTouch() const
{
	CPP_TouchEffectWidget->ActivateSystem(true);
}
