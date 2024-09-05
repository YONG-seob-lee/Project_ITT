// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ITT_StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_StateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	void Create();
	void Destroy();
	void Tick(float DeltaTime);

	void RegistState(int8 Index, const FName& Name, TSubclassOf<class UITT_StateBase> SceneType, UObject* Outer = nullptr);
	void UnRegistStates();

	TObjectPtr<UITT_StateBase> GetCurrentState();

	void GetActiveStateId(TArray<int8>& ActiveState) const;

	void SetState(int32 Index, bool _bInstant = true);

	TObjectPtr<UITT_StateBase> GetState(int32 Index) const;
private:
	void SetState_Internal(uint8 Index);
	
	UPROPERTY()
	TMap<int8, TObjectPtr<UITT_StateBase>> EntireState;

	uint8 PreviousStateId = -1;
	uint8 CurrentStateId = -1;
	uint8 ChangeStateId = -1;
};
