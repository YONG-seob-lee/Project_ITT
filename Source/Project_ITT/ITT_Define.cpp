// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Define.h"

#include "Table/ITT_TableMapper.h"

DEFINE_LOG_CATEGORY(My_Log);

void FITT_TableMapperData::Finalize()
{
	TablePath = nullptr;
	TableData = nullptr;
	
	if(IsValid(TableMapper))
	{
		TableMapper->Finalize();
		ITT_DeleteObject(TableMapper);
	}
}