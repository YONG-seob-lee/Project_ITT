// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_WidgetManager.h"

#include "ITT_TableManager.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Table/Resource_Widget.h"
#include "PROJECT_ITT/Table/Mapper/ITT_Mapper_Resource_Widget.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "Tool/WidgetTool/ITT_BuiltInWidgetTool.h"

void UITT_WidgetManager::BuiltInInitialize()
{
	BuiltInTool = ITT_NewObject<UITT_BuiltInWidgetTool>(this, TEXT("BuiltInWidgetTool"));
	if(IsValid(BuiltInTool.Get()) == false)
	{
		return;
	}

	BuiltInTool->BuiltInitialize();
}

void UITT_WidgetManager::Initialize()
{
	BuiltInTool->Initialize();
}

void UITT_WidgetManager::Finalize()
{
	ClearExclusiveLayer();
	ManagedWidgets.Empty();
}

void UITT_WidgetManager::BuiltInFinalize()
{
	if(IsValid(BuiltInTool.Get()))
	{
		BuiltInTool->Finalize();
		ITT_DeleteObject(BuiltInTool);
		BuiltInTool = nullptr;
	}
}

void UITT_WidgetManager::Tick(float DeltaTime)
{
	if(BuiltInTool)
	{
		BuiltInTool->Tick(DeltaTime);
	}
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::GetWidget(const FName& TypeName)
{
	const TWeakObjectPtr<UITT_Widget>* pWidget = ManagedWidgets.Find(TypeName);
	if(pWidget && pWidget->IsValid())
	{
		return pWidget->Get();
	}

	return nullptr;
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::Create_Widget(const FName& TypeName)
{
	GEngine->ForceGarbageCollection(true);

	if(const TWeakObjectPtr<UITT_Widget>* pWidget = ManagedWidgets.Find(TypeName))
	{
		const TWeakObjectPtr<UITT_Widget>& PreviousWidget = *pWidget;
		if(PreviousWidget.IsValid())
		{
			return PreviousWidget.Get();
		}
		ManagedWidgets.Remove(TypeName);
	}

	const TObjectPtr<UITT_Widget> Widget = Cast<UITT_Widget>(CreateWidget_Internal(TypeName, true));
	ITT_CHECK(Widget != nullptr);

	AddExclusiveLayerWidget(Widget);
	
	ManagedWidgets.Emplace(TypeName, Widget);

	if(OnCreateWidget.IsBound())
	{
		OnCreateWidget.Broadcast(TypeName);
	}
	
	return Widget;
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::Create_Widget_NotManaging(const FSoftObjectPath& SoftObjectPath)
{
	const TObjectPtr<UITT_Widget> Widget = CreateWidget_Internal_NotManaging(SoftObjectPath.ToString());
	if(Widget == nullptr)
	{
		ITT_CHECK(false);
		return nullptr;
	}
	
	return Widget;
}

void UITT_WidgetManager::PreDestroyWidget(TObjectPtr<UITT_Widget> Widget)
{
	if(IsValid(Widget) == false)
	{
		return;
	}

	RemoveExclusiveLayerWidget(Widget);

	if(OnDestroyWidget.IsBound())
	{
		OnDestroyWidget.Broadcast(Widget->GetResourceWidgetInfo().GetWidgetName());
	}
}

bool UITT_WidgetManager::DestroyWidget(const FName& TypeName)
{
	TObjectPtr<UITT_Widget> Widget = GetWidget(TypeName);
	if(Widget == nullptr)
	{
		return false;
	}

	PreDestroyWidget(Widget);
	Widget->FinishWidget();

	ManagedWidgets.Remove(TypeName);
	Widget = nullptr;
	PostDestroyWidget(TypeName);	
	return true;
}

void UITT_WidgetManager::PostDestroyWidget(const FName& TypeName)
{
}

void UITT_WidgetManager::ClearExclusiveLayer()
{
	constexpr uint8 Top = static_cast<uint8>(EITT_ExclusiveGroup::TopMenu);
	constexpr uint8 Content = static_cast<uint8>(EITT_ExclusiveGroup::ContentMenu);

	if(ExclusiveLayers.IsValidIndex(Top))
	{
		ExclusiveLayers[Top] = nullptr;
	}
	if(ExclusiveLayers.IsValidIndex(Content))
	{
		ExclusiveLayers[Content] = nullptr;
	}
}

void UITT_WidgetManager::Test(UITT_Widget* Widget)
{
	ManagedWidgets.Emplace(TEXT("Fader"), Widget);
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::CreateWidget_Internal(const FName& TypeName, bool bManaged)
{
	const TObjectPtr<UITT_Mapper_Resource_Widget> ResourceWidgetMapper = Cast<UITT_Mapper_Resource_Widget>(gTableMng.GetTableMapper(EITT_TableDataType::Resource_Widget));
	if(ResourceWidgetMapper == nullptr)
	{
		return nullptr;
	}

	const FResource_Widget* ResourceWidgetData = ResourceWidgetMapper->GetResourceWidgetData(TypeName);
	if(ResourceWidgetData == nullptr)
	{
		// 테이블 자료 문제
		return nullptr;
	}

	const FString ResourcePath = gTableMng.GetPath(EITT_TableDataType::BasePath_BP_File, ResourceWidgetData->Path_File, true);

	const TObjectPtr<UITT_Widget> ResultWidget = bManaged ? CreateWidget_Internal_Managing(ResourcePath) : CreateWidget_Internal_NotManaging(ResourcePath);

	if(ResultWidget == nullptr)
	{
		return nullptr;
	}

	FITT_ResourceWidgetInfo WidgetInfo;
	WidgetInfo.TypeName = ResourceWidgetData->TypeName;
	WidgetInfo.File = ResourcePath;
	WidgetInfo.zOrder = ResourceWidgetData->zOrder;
	WidgetInfo.ExclusiveGroup = static_cast<EITT_ExclusiveGroup>(ResourceWidgetData->ExclusiveGroup);
	WidgetInfo.NotRender3D = ResourceWidgetData->NotRender3D;

	ResultWidget->SetZOrder(WidgetInfo.zOrder);
	ResultWidget->SetResourceWidgetInfo(WidgetInfo);
	ResultWidget->InitWidget(TypeName, bManaged);

	return ResultWidget;
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::CreateWidget_Internal_Managing(const FString& Path)
{
	static FString SubName = TEXT("Create Widget");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(UITT_InstUtil::LoadObjectFromFile(Path, FITT_LoadResourceDelegate::CreateUObject(this, &UITT_WidgetManager::LoadComplete)));
	if(WidgetClass == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
	if(World == nullptr)
	{
		return nullptr;
	}

	return CreateWidget<UITT_Widget>(World, WidgetClass);
}

TObjectPtr<UITT_Widget> UITT_WidgetManager::CreateWidget_Internal_NotManaging(const FString& Path) const
{
	static FString SubName = TEXT("Create Widget");
	const FString ClassName = Path + TEXT("_C");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(UITT_InstUtil::LoadObjectFromFile(ClassName));
	const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
	
	if(World != nullptr && World->bIsTearingDown == false)
	{
		if(const TObjectPtr<UITT_Widget> Widget = CreateWidget<UITT_Widget>(World, WidgetClass))
		{
			Widget->Init();
			return Widget;
		}
	}
	
	return nullptr;
}

void UITT_WidgetManager::AddExclusiveLayerWidget(TObjectPtr<UITT_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());
	if(GroupIndex != 0)
	{
		if(ExclusiveLayers.IsValidIndex(GroupIndex) && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
		{
			const TObjectPtr<UITT_Widget> PreviousWidget = ExclusiveLayers[GroupIndex];
			if(IsValid(PreviousWidget))
			{
				DestroyWidget(PreviousWidget->GetResourceWidgetInfo().GetWidgetName());
			}
		}

		ExclusiveLayers[GroupIndex] = Widget;
	}
}

void UITT_WidgetManager::RemoveExclusiveLayerWidget(TObjectPtr<UITT_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());

	if(GroupIndex != 0 && ExclusiveLayers.Num() > 0 && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
	{
		ExclusiveLayers[GroupIndex] = nullptr;
	}
}

void UITT_WidgetManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData)
{
}
