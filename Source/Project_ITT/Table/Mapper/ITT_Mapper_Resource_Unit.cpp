// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Mapper_Resource_Unit.h"

#include "PROJECT_ITT/Table/Resource_Unit.h"

void UITT_Mapper_Resource_Unit::Initialize(TObjectPtr<UITT_TableManager> Mng)
{
	Super::Initialize(Mng);
	
	TMap<int32, FResource_Unit*> PrimitiveResourceUnit;
	PrimitiveResourceUnit.Empty();
	
	BuildTable(Mng, EITT_TableDataType::Resource_Widget, PrimitiveResourceUnit);

	for(const auto& ResourceUnitData : PrimitiveResourceUnit)
	{
		ResourceUnits.Emplace(ResourceUnitData.Key, ResourceUnitData.Value);
	}
}

void UITT_Mapper_Resource_Unit::Finalize()
{
	ResourceUnits.Empty();
	
	Super::Finalize();
}

FResource_Unit* UITT_Mapper_Resource_Unit::GetResourceUnitData(ITT_Handle _UnitHandle)
{
	if(FResource_Unit** UnitData =  ResourceUnits.Find(_UnitHandle))
	{
		return *UnitData;
	}

	return nullptr;
}
