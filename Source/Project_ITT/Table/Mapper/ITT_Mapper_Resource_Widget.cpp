// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Mapper_Resource_Widget.h"

#include "PROJECT_ITT/Table/Resource_Widget.h"

void UITT_Mapper_Resource_Widget::Initialize(TObjectPtr<UITT_TableManager> Mng)
{
	Super::Initialize(Mng);

	TMap<int32, FResource_Widget*> PrimitiveResourceWidget;
	PrimitiveResourceWidget.Empty();
	
	BuildTable(Mng, EITT_TableDataType::Resource_Widget, PrimitiveResourceWidget);

	for(const auto& ResourceWidgetData : PrimitiveResourceWidget)
	{
		ResourceWidgetDatas.Emplace(ResourceWidgetData.Value->TypeName, ResourceWidgetData.Value);
	}
}

void UITT_Mapper_Resource_Widget::Finalize()
{
	ResourceWidgetDatas.Empty();

	Super::Finalize();
}

FResource_Widget* UITT_Mapper_Resource_Widget::GetResourceWidgetData(const FName& TypeName)
{
	if(FResource_Widget** pResourceWidgetData = ResourceWidgetDatas.Find(TypeName))
	{
		return *pResourceWidgetData;
	}

	return nullptr;
}
