// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Table/ITT_TableMapper.h"
#include "PROJECT_ITT/Table/Select_Button.h"
#include "ITT_Mapper_SelectButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Mapper_SelectButton : public UITT_TableMapper
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UITT_TableManager> Mng) override;
	virtual void Finalize() override;

	TMap<int32, FSelectButton*>* GetSelectButtonDatas();

private:
	TMap<int32, FSelectButton*> SelectButtonDatas;
};
