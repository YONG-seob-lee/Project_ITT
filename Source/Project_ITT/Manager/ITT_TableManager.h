// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "ITT_TableManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_TableManager : public UObject, public UITT_Singleton<UITT_TableManager>
{
	GENERATED_BODY()

public:
	UITT_TableManager();
	~UITT_TableManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	virtual void GetRowDataMap(EITT_TableDataType TableType, TMap<FName, uint8*>& OutMapper);

	FITT_TableMapperData* GetTableMapperData(EITT_TableDataType TableType);
	FString GetPath(EITT_TableDataType TableType, int32 Key, bool bResourcePath = false);
	FString GetDirectory(int32 DirectoryTableId);
	
	TObjectPtr<UDataTable> GetTableData(EITT_TableDataType TableType);

	
	TObjectPtr<UITT_TableMapper> GetTableMapper(EITT_TableDataType TableType);
	
	template<typename FRowData>
	FRowData* GetTableRowData(EITT_TableDataType TableType, int32 Key)
	{
		const FITT_TableMapperData* TableMapper = GetTableMapperData(TableType);
		if (TableMapper == nullptr)  
		{
			return nullptr;
		}

		const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
		const FName KeyName = FName(FString::FromInt(Key));
		const FString Context = TEXT("GENERAL");
		return TableData->FindRow<FRowData>(KeyName, Context);
	}

	int32 GetTableRowNum(EITT_TableDataType TableType)
	{
		const FITT_TableMapperData* TableMapper = GetTableMapperData(TableType);
		if (TableMapper == nullptr)
		{
			return 0;
		}

		if(const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData())
		{
			return TableData->GetRowMap().Num();
		}
		return 0;
	}

private:
	void ResetData();
	void CreateTableData(EITT_TableDataType TableType, const FString& Path, TSubclassOf<UITT_TableMapper> MapperType = nullptr);
	void MakeTableStructData();

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData);
	
	UPROPERTY()
	TMap<EITT_TableDataType, FITT_TableMapperData> TableMappers;

	bool bInitialize = false;
	
#define	gTableMng (*UITT_TableManager::GetInstance())
};