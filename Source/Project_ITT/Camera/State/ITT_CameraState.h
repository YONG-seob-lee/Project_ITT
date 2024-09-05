// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"
#include "ITT_CameraState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CameraState : public UITT_StateBase
{
	GENERATED_BODY()

protected:
	virtual void InitCamera() { }
};
