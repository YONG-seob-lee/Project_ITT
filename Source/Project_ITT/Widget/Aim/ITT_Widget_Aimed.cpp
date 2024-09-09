// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Aimed.h"
#include "Components/Image.h"


void UITT_Widget_Nail::FallOutNail(bool bFailOut /* = true */)
{
	if(bFailOut)
	{
		CPP_Full->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_Full->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		PlayAnimation(ReturnNail);
	}
}


void UITT_Widget_Aimed::NativeConstruct()
{
	Super::NativeConstruct();

	NailCount.Emplace(1, CPP_Nail_01);
	NailCount.Emplace(2, CPP_Nail_02);
	NailCount.Emplace(3, CPP_Nail_03);
}

void UITT_Widget_Aimed::NailMovement(int32 NailIndex, bool bThrowNail/* = true */)
{
	if(const TObjectPtr<UITT_Widget_Nail>* TargetNail = NailCount.Find(NailIndex))
	{
		(*TargetNail)->FallOutNail(bThrowNail);
	}
}