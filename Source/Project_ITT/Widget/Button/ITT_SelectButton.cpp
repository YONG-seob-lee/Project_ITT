// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SelectButton.h"

#include "Components/TextBlock.h"

void UITT_SelectButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UITT_SelectButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UITT_SelectButton::SetButtonData(const FString& ButtonName) const
{
	if(CPP_ButtonName)
	{
		CPP_ButtonName->SetText(FText::FromString(ButtonName));
	}
}
