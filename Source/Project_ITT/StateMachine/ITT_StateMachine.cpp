// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_StateMachine.h"

#include "ITT_StateBase.h"
#include "PROJECT_ITT/ITT_Define.h"

void UITT_StateMachine::Create()
{
}

void UITT_StateMachine::Destroy()
{
}

void UITT_StateMachine::Tick(float DeltaTime)
{
	for(const auto& State : EntireState)
	{
		State.Value->Tick(DeltaTime);
	}
}

void UITT_StateMachine::RegistState(int8 Index, const FName& Name, TSubclassOf<UITT_StateBase> SceneType, UObject* Outer)
{
	if (EntireState.Find(Index) != nullptr)
	{
		ITT_CHECK(false);
		return;
	}

	const TObjectPtr<UObject> CustomOuter = Outer != nullptr ? Outer : this;
	TObjectPtr<UITT_StateBase> State = ITT_NewObject<UITT_StateBase>(CustomOuter, SceneType);

	State->AddToRoot();
	State->Initialize(Index, Name);
	EntireState.Emplace(Index, State);
}

void UITT_StateMachine::UnRegistStates()
{
	for (auto& State : EntireState)
	{
		if (State.Value != nullptr)
		{
			State.Value->Finalize();
			State.Value->RemoveFromRoot();
			State.Value = nullptr;
		}
	}

	EntireState.Empty();
}

TObjectPtr<UITT_StateBase> UITT_StateMachine::GetCurrentState()
{
	const TObjectPtr<UITT_StateBase>* pCurrentStateBase = EntireState.Find(CurrentStateId);

	return pCurrentStateBase ? *pCurrentStateBase : nullptr;
}

void UITT_StateMachine::GetActiveStateId(TArray<int8>& ActiveState) const
{
	if(EntireState.IsEmpty())
	{
		return;
	}
	
	ActiveState.Empty();
	return EntireState.GenerateKeyArray(ActiveState);
}

void UITT_StateMachine::SetState(int32 Index, bool _bInstant)
{
	if(_bInstant)
	{
		SetState_Internal(Index);
	}
	else
	{
		ChangeStateId = Index;
	}
}

TObjectPtr<UITT_StateBase> UITT_StateMachine::GetState(int32 Index) const
{
	if(EntireState.Contains(Index))
	{
		return EntireState[Index];
	}

	return nullptr;
}

void UITT_StateMachine::SetState_Internal(uint8 Index)
{
	PreviousStateId = CurrentStateId;

	if(const TObjectPtr<UITT_StateBase> CurrentState = GetState(CurrentStateId))
	{
		CurrentState->OnExitState();
	}

	CurrentStateId = Index;

	if(const TObjectPtr<UITT_StateBase> NextState = GetState(Index))
	{
		NextState->OnBeginState();
	}
}
