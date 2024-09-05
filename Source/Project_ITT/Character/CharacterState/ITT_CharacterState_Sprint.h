// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_CharacterState.h"
#include "ITT_CharacterState_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CharacterState_Sprint : public UITT_CharacterState
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime);
	
protected:
	virtual void Begin();
	virtual void Exit();
};
