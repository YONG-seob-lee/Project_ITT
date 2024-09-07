// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_AnimInstance_Rose.h"

#include "ITT_InstUtil.h"

void UITT_AnimInstance_Rose::Initialize()
{
	SelectValue = EITT_SelectCharacter::None;
}

void UITT_AnimInstance_Rose::Finalize()
{
}

void UITT_AnimInstance_Rose::Select(EITT_SelectCharacter _SelectValue)
{
	SelectValue = _SelectValue;
	UITT_InstUtil::ShowMessageOnScreen(TEXT("Select"));
}