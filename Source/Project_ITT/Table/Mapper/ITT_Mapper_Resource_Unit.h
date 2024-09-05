// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Table/ITT_TableMapper.h"
#include "ITT_Mapper_Resource_Unit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Mapper_Resource_Unit : public UITT_TableMapper
{
	GENERATED_BODY()
	
	
public:
	virtual void Initialize(TObjectPtr<UITT_TableManager> Mng) override;
	virtual void Finalize() override;
	
	struct FResource_Unit* GetResourceUnitData(ITT_Handle _UnitHandle);
	
private:
	TMap<int32, FResource_Unit*> ResourceUnits;
};
