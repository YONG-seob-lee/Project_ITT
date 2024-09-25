// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_UnitBase.h"

#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "PROJECT_ITT/Manager/ITT_TableManager.h"
#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/StateMachine/ITT_StateMachine.h"
#include "PROJECT_ITT/Table/Resource_Unit.h"

void UITT_UnitBase::Initialize()
{
}

void UITT_UnitBase::Finalize()
{
	DestroyUnit();
	OnActorTickDelegate.RemoveAll(this);
}

void UITT_UnitBase::PostInitialize()
{
}

void UITT_UnitBase::Tick(float DeltaTime)
{
	OnActorTickDelegate.Broadcast(this);

	if(ActionStateMachine)
	{
		ActionStateMachine->Tick(DeltaTime);
	}
}

bool UITT_UnitBase::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	ResourceUnitTableId = UnitTableId;
	ResourceUnitData = gTableMng.GetTableRowData<FResource_Unit>(EITT_TableDataType::Resource_Unit, ResourceUnitTableId);
	if(ResourceUnitData == nullptr)
	{
		return false;
	}

	const FString BPPath = gTableMng.GetPath(EITT_TableDataType::BasePath_BP_File, ResourceUnitData->Base_Path, true);
	if(const TObjectPtr<AITT_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, Pos, Rot))
	{
		CharacterBase = NewCharacter;
		CharacterBase->SetOwnerUnitBase(this);
		
		if(const TObjectPtr<UITT_AnimInstance> AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
		{
			AnimInstance->SetMoveSpeedInfo(ResourceUnitData->WalkSpeed, ResourceUnitData->RunSpeed);
			AnimInstance->InitializeAnimation();
		}
	}
	
	return true;
}

void UITT_UnitBase::DestroyUnit()
{
}

void UITT_UnitBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(IsValidCharacterActor())
	{
		CharacterBase->SetLodScaleValues(CullDistanceScale, OutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UITT_UnitBase::SetUnitPosition(const FVector& NewSpawnUnitPosition) const
{
	if(CharacterBase == nullptr)
	{
		return;
	}

	CharacterBase->SetActorLocation(NewSpawnUnitPosition);
}

TObjectPtr<UAnimInstance> UITT_UnitBase::GetAnimInstance() const
{
	if(const TObjectPtr<AITT_CharacterBase> Character = GetCharacterBase())
	{
		return Character->GetAnimInstance();
	}

	return nullptr; 	
}

float UITT_UnitBase::GetMovingSpeed() const
{
	if(const TObjectPtr<UITT_AnimInstance> AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
	{
		return AnimInstance->GetMovingSpeed();
	}

	return 0.f;
}

bool UITT_UnitBase::CreateActionStateMachine()
{
	if(UnitHandle == InvalidUnitHandle)
	{
		return false;
	}

	if(CharacterBase == nullptr)
	{
		return false;
	}

	ActionStateMachine = ITT_NewObject<UITT_StateMachine>(this, UITT_StateMachine::StaticClass());
	ActionStateMachine->AddToRoot();
	ActionStateMachine->Create();

	return true;
}

void UITT_UnitBase::DestroyActionStateMachine()
{
	if(ActionStateMachine)
	{
		ActionStateMachine->Destroy();
		ActionStateMachine->RemoveFromRoot();
		ActionStateMachine = nullptr;
	}
}

void UITT_UnitBase::AddActionState(EITT_UnitActionState State, const FName& Name, TSubclassOf<UITT_StateBase> ClassType)
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}

	ActionStateMachine->RegistState(static_cast<uint8>(State), Name, ClassType, this);
}

void UITT_UnitBase::ChangeActionState(EITT_UnitActionState ActionType) const
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}
	
	ActionStateMachine->SetState(static_cast<uint8>(ActionType));
}

TObjectPtr<UActorComponent> UITT_UnitBase::GetActorComponentByTag(TSubclassOf<UActorComponent> ClassType, FName TabName,
	bool bIncludeFromChildActors) const
{
	const TObjectPtr<AITT_CharacterBase> TargetCharacter = GetCharacterBase();
	if(TargetCharacter == nullptr)
	{
		return nullptr;
	}

	TInlineComponentArray<UActorComponent*> Components;
	TargetCharacter->GetComponents(ClassType, Components, bIncludeFromChildActors);

	for(int32 i = 0; i < Components.Num() ; ++i)
	{
		if(Components[i]->ComponentHasTag(TabName))
		{
			return Components[i];
		}
	}

	return nullptr;
}
