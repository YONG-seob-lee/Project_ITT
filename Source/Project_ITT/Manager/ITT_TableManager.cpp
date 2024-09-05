// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_TableManager.h"

#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Table/BasePath_BP_File.h"
#include "PROJECT_ITT/Table/BasePath_Directory.h"
#include "PROJECT_ITT/Table/BasePath_Img_File.h"
#include "PROJECT_ITT/Table/ITT_TableMapper.h"
#include "PROJECT_ITT/Table/Mapper/ITT_Mapper_Resource_Unit.h"
#include "PROJECT_ITT/Table/Mapper/ITT_Mapper_Resource_Widget.h"
#include "PROJECT_ITT/Table/Mapper/ITT_Mapper_SelectButton.h"

UITT_TableManager::UITT_TableManager()
{
}

UITT_TableManager::~UITT_TableManager()
{
}

void UITT_TableManager::Initialize()
{
	if(bInitialize)
	{
		return;
	}
	MakeTableStructData();

	bInitialize = true;
}

void UITT_TableManager::Finalize()
{
	for (auto& TableMapper : TableMappers)
	{
		TableMapper.Value.Finalize();
	}

	TableMappers.Empty();
}

void UITT_TableManager::Tick(float DeltaTime)
{
	UITT_Singleton<UITT_TableManager>::Tick(DeltaTime);
}

void UITT_TableManager::GetRowDataMap(EITT_TableDataType TableType, TMap<FName, uint8*>& OutMapper)
{
	const FString& Name = UITT_InstUtil::ConvertEnumToString<EITT_TableDataType>("EITT_TableDataType", TableType);

	const FITT_TableMapperData* TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		return;
	}

	const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
	if (TableData == nullptr)
	{
		return;
	}

	OutMapper = TableData->GetRowMap();
}

FITT_TableMapperData* UITT_TableManager::GetTableMapperData(EITT_TableDataType TableType)
{
	FITT_TableMapperData* TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		const FString& TableName = UITT_InstUtil::ConvertEnumToString<EITT_TableDataType>("EITT_TableDataType", TableType);
		ITT_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return TableMapper;
}

FString UITT_TableManager::GetPath(EITT_TableDataType TableType, int32 Key, bool bResourcePath)
{
	switch(TableType)
	{
	case EITT_TableDataType::BasePath_BP_File:
		{
			const FBasePath_BP_File* RowData = GetTableRowData<FBasePath_BP_File>(TableType, Key);

			if(RowData == nullptr)
			{
				return FString();
			}
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->BP_File_Name.ToString() + '.' + RowData->BP_File_Name.ToString() + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->BP_File_Name.ToString()});
		}
		break;
	case EITT_TableDataType::BasePath_Img_File:
		{
			const FBasePath_Img_File* RowData = GetTableRowData<FBasePath_Img_File>(TableType, Key);
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->Img_File_Name + '.' + RowData->Img_File_Name + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->Img_File_Name});
		}
		break;
	default:
		return FString();
	}

	return FString();
}

FString UITT_TableManager::GetDirectory(int32 DirectoryTableId)
{
	if(DirectoryTableId == 0 || DirectoryTableId == INDEX_NONE)
	{
		return FString();
	}

	const FBasePath_Directory* RowData = GetTableRowData<FBasePath_Directory>(EITT_TableDataType::BasePath_Directory, DirectoryTableId);
	if(RowData == nullptr)
	{
		return FString();
	}
	
	FString ResultDirectory = RowData->Directory.StartsWith(TEXT("/Game/")) ? RowData->Directory : TEXT("/Game/") + RowData->Directory;
	
	return ResultDirectory[ResultDirectory.Len() - 1] != '/' ? ResultDirectory + "/" : ResultDirectory;
}

TObjectPtr<UDataTable> UITT_TableManager::GetTableData(EITT_TableDataType TableType)
{
	const FITT_TableMapperData* TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableData();
}

TObjectPtr<UITT_TableMapper> UITT_TableManager::GetTableMapper(EITT_TableDataType TableType)
{
	const FITT_TableMapperData* TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableMapper();
}


void UITT_TableManager::ResetData()
{
	TableMappers.Empty();
}

void UITT_TableManager::CreateTableData(EITT_TableDataType TableType, const FString& Path, TSubclassOf<UITT_TableMapper> MapperType)
{
	const FString& TableName = UITT_InstUtil::ConvertEnumToString<EITT_TableDataType>("EITT_TableDataType", TableType);

	if (TableMappers.Find(TableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	const TObjectPtr<UDataTable> TableObject = UITT_InstUtil::LoadTableObjectFromFile(Path, TableName, FITT_LoadResourceDelegate::CreateUObject(this, &UITT_TableManager::LoadComplete));
	if (TableObject == nullptr)
	{
		return;
	}

	// 매퍼 생성 및 초기화
	if(MapperType)
	{
		const TObjectPtr<UITT_TableMapper> TableMapper = ITT_NewObject<UITT_TableMapper>(this, MapperType);
		if (TableMapper == nullptr)
		{
			return;
		}
		// 추가.
		TableMappers.Emplace(TableType, FITT_TableMapperData(Path, TableObject, TableMapper));
		
		TableMapper->Initialize(this);
	}
	else
	{
		TableMappers.Emplace(TableType, FITT_TableMapperData(Path, TableObject, nullptr));
	}
}

void UITT_TableManager::MakeTableStructData()
{
	ResetData();

	// 테이블 데이터 추가
	CreateTableData(EITT_TableDataType::BasePath_Directory, "/Game/TableData/BasePath_Directory.BasePath_Directory");
	CreateTableData(EITT_TableDataType::BasePath_BP_File, "/Game/TableData/BasePath_BP_File.BasePath_BP_File");
	CreateTableData(EITT_TableDataType::BasePath_Img_File, "/Game/TableData/BasePath_Img_File.BasePath_Img_File");
	CreateTableData(EITT_TableDataType::Resource_Widget, "/Game/TableData/Resource_Widget.Resource_Widget", UITT_Mapper_Resource_Widget::StaticClass());
	CreateTableData(EITT_TableDataType::Resource_Unit, "/Game/TableData/Resource_Unit.Resource_Unit", UITT_Mapper_Resource_Unit::StaticClass());
	CreateTableData(EITT_TableDataType::SelectButton, "/Game/TableData/SelectButton.SelectButton", UITT_Mapper_SelectButton::StaticClass());
}

void UITT_TableManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData)
{
}