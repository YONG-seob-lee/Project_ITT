// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_AnimInstance_Doll.h"

void UITT_AnimInstance_Doll::Initialize()
{
	SelectValue = 0.f;
}

void UITT_AnimInstance_Doll::Finalize()
{
}

void UITT_AnimInstance_Doll::Select(float _SelectValue)
{
	SelectValue = _SelectValue;
}
