// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Scene/ITT_SceneBase.h"
#include "ITT_SceneState_Logo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SceneState_Logo : public UITT_SceneBase
{
	GENERATED_BODY()
	
protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
};
