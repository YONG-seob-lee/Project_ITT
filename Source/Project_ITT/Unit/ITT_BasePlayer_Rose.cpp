// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer_Rose.h"

#include "UnitState/ITT_State_SelectPick.h"
#include "UnitState/ITT_State_SelectPickMove.h"

void UITT_BasePlayer_Rose::Initialize()
{
	Super::Initialize();
}

void UITT_BasePlayer_Rose::Finalize()
{
	Super::Finalize();
}

void UITT_BasePlayer_Rose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool UITT_BasePlayer_Rose::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	Super::CreateUnit(UnitTableId, Pos, Rot);
	
	if(CreateActionStateMachine())
	{
		AddActionState(EITT_UnitActionState::Select_PickMove, TEXT("Character_PickMove"), UITT_State_SelectPickMove::StaticClass());
		AddActionState(EITT_UnitActionState::Select_Pick, TEXT("Character_Pick"), UITT_State_SelectPick::StaticClass());
	}
	
	ChangeActionState(EITT_UnitActionState::Select_PickMove);
	
	return true;
}

void UITT_BasePlayer_Rose::DestroyUnit()
{
	Super::DestroyUnit();
}

void UITT_BasePlayer_Rose::SetDollAnimInst(const TObjectPtr<UITT_AnimInstance_Doll>& MayDollInst,
	const TObjectPtr<UITT_AnimInstance_Doll>& CodyDollInst)
{
	if(MayDollInst)
	{
		MayDollAnim = MayDollInst;
	}

	if(CodyDollInst)
	{
		CodyDollAnim = CodyDollInst;
	}
}

TWeakObjectPtr<UITT_AnimInstance_Doll> UITT_BasePlayer_Rose::GetDollAnimInstance(int32 DollIndex)
{
	if(DollIndex == 0)
	{
		return MayDollAnim.Get();
	}
	else if(DollIndex == 1)
	{
		return CodyDollAnim.Get();
	}
	else
	{
		return nullptr;
	}
}
