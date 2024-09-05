// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/ITT_StateBase.h"
#include "ITT_Define.h"
#include "ITT_CharacterState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CharacterState : public UITT_StateBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(uint8 Index, const FName& Name);
	virtual void Finalize();
	
	EITT_CharacterState GetCharacterState() const { return CharacterState; }
	
private:
	UPROPERTY()
	EITT_CharacterState CharacterState;
};
