// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"
#include "ITT_SceneBase.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FITT_LoadingProcessDelegate, float);
/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SceneBase : public UITT_StateBase
{
	GENERATED_BODY()
	

protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

public:
	void TickLoading(float DeltaTime);
	bool IsCompleteLoading();

protected:
	virtual bool LoadingPreProcess(float DeltaTime);
	virtual bool LoadingProcess(float DeltaTime);
	virtual bool LoadingPostProcess(float DeltaTime);

private:
	TArray<FITT_LoadingProcessDelegate> LoadingProcessDelegates;
};
