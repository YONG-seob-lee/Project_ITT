// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Mapper_SelectButton.h"

void UITT_Mapper_SelectButton::Initialize(TObjectPtr<UITT_TableManager> Mng)
{
	Super::Initialize(Mng);

	BuildTable(Mng, EITT_TableDataType::SelectButton, SelectButtonDatas);
}

void UITT_Mapper_SelectButton::Finalize()
{
	SelectButtonDatas.Empty();

	Super::Finalize();
}

TMap<int32, FSelectButton*>* UITT_Mapper_SelectButton::GetSelectButtonDatas()
{
	return &SelectButtonDatas;
}
