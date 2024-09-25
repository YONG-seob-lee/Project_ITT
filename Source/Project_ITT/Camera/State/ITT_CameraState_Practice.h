// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_CameraState.h"
#include "ITT_CameraState_Practice.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CameraState_Practice : public UITT_CameraState
{
	GENERATED_BODY()
public:
	UITT_CameraState_Practice();
	virtual ~UITT_CameraState_Practice() override;
	
	virtual void Initialize(uint8 Index, const FName& Name) override;
	virtual void Finalize() override;
	
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
\
	
private:
	
	UPROPERTY()
	TObjectPtr<class AITT_Actor_Camera> May_Camera;
};
