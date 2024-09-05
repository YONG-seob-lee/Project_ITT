// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_StateBase.h"

#include "ITT_StateMachine.h"

void UITT_StateBase::Initialize(uint8 Index, const FName& Name)
{
	StateIndex = Index;
	StateName = Name;
}

void UITT_StateBase::Finalize()
{
}

void UITT_StateBase::OnBeginState()
{
	Begin();
}

void UITT_StateBase::OnTickState()
{
	//Tick();
}

void UITT_StateBase::OnExitState()
{
	Exit();
}

TObjectPtr<UITT_StateMachine> UITT_StateBase::GetStateMachine() const
{
	return Cast<UITT_StateMachine>(GetOuter());
}
