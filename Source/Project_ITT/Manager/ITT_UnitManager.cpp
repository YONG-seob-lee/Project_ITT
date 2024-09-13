// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_UnitManager.h"

#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/ITT_PlayerController.h"
#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "PROJECT_ITT/Unit/ITT_BasePlayer.h"
#include "PROJECT_ITT/Unit/ITT_UnitBase.h"

void UITT_UnitManager::Initialize()
{
	UITT_Singleton<UITT_UnitManager>::Initialize();
}

void UITT_UnitManager::Finalize()
{
	DestroyAllUnit();
}

void UITT_UnitManager::Tick(float _DeltaTime)
{
	for(const auto& Unit : Units)
	{
		Unit.Value->Tick(_DeltaTime);
	}
}

TObjectPtr<UITT_UnitBase> UITT_UnitManager::CreateUnit(int32 UnitTableId, TSubclassOf<UITT_UnitBase> UnitType,
	const FVector& Position, const FRotator& Rotator)
{
	const TObjectPtr<UITT_UnitBase> Unit = ITT_NewObject<UITT_UnitBase>(this, UnitType);
	Unit->AddToRoot();
	Unit->Initialize();
	
	if(Unit->CreateUnit(UnitTableId, Position, Rotator) == false)
	{
		return nullptr;
	}

	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	const ITT_Handle NewUnitHandle = MakeUnitHandle(Unit);
	
	if(NewUnitHandle == InvalidUnitHandle)
	{
		return nullptr;
	}
	
	Units.Add(NewUnitHandle, Unit);
	
	return Unit;
}

TObjectPtr<UITT_UnitBase> UITT_UnitManager::GetCurrentUnit()
{
	const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(UITT_InstUtil::GetPlayerController());
	if(PlayerController == nullptr)
	{
		return nullptr;
	}
	
	return gUnitMng.GetUnit(PlayerController->GetUnitHandle());
}

void UITT_UnitManager::DestroyUnit(ITT_Handle UnitHandle)
{
	if(Units.Find(UnitHandle) != nullptr)
	{
		Units[UnitHandle]->RemoveFromRoot();
		Units[UnitHandle]->Finalize();
		Units[UnitHandle]->MarkAsGarbage();
		Units[UnitHandle] = nullptr;
		Units.Remove(UnitHandle);
	}
}

void UITT_UnitManager::DestroyAllUnit()
{
	for(auto& Unit : Units)
	{
		if(Unit.Value == nullptr)
		{
			continue;
		}

		Unit.Value->RemoveFromRoot();
		Unit.Value->Finalize();
		Unit.Value->MarkAsGarbage();
		Unit.Value = nullptr;
	}
}

TObjectPtr<AITT_CharacterBase> UITT_UnitManager::CreateCharacter(const FString& BlueprintPath, const FVector& Pos,
	const FRotator& Rot)
{
	const TObjectPtr<AITT_CharacterBase> NewCharacter = Cast<AITT_CharacterBase>(UITT_InstUtil::SpawnBlueprintActor(BlueprintPath, Pos, Rot));
	if(IsValid(NewCharacter))
	{
		NewCharacter->Create(UITT_InstUtil::GetBPNameFromFullPath(BlueprintPath));
		return NewCharacter;
	}

	return nullptr;	
}

TObjectPtr<UITT_UnitBase> UITT_UnitManager::GetUnit(ITT_Handle UnitHandle)
{
	const TObjectPtr<UITT_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? *pUnit : nullptr;
}

TObjectPtr<UITT_UnitBase> UITT_UnitManager::GetUnitTableId(ITT_Character TableId)
{
	for(const auto& Unit : Units)
	{
		if(Unit.Value->GetUnitTableId() == TableId)
		{
			return Unit.Value;
		}
	}

	return nullptr;
}

ITT_Handle UITT_UnitManager::GetUnitHandle(TObjectPtr<UITT_UnitBase> UnitBase) const
{
	const ITT_Handle* UnitHandle = Units.FindKey(UnitBase);

	return UnitHandle ? *UnitHandle : InvalidUnitHandle;
}

TObjectPtr<AITT_CharacterBase> UITT_UnitManager::GetCharacterBase(ITT_Handle UnitHandle)
{
	const TObjectPtr<UITT_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? (*pUnit)->GetCharacterBase() : nullptr;
}

ITT_Handle UITT_UnitManager::GetIsValidBasePlayer()
{
	for(const auto& Unit : Units)
	{
		if(const TObjectPtr<UITT_BasePlayer> BasePlayer = Cast<UITT_BasePlayer>(Unit.Value))
		{
			return BasePlayer->GetUnitHandle();			
		}
	}

	return InvalidUnitHandle;
}

ITT_Handle UITT_UnitManager::MakeUnitHandle(const TObjectPtr<UITT_UnitBase> Unit) const
{
	const int32 UnitNum = Units.Num();
	const int32 NextUnitIndex = UnitNum + 1;

	if(Units.Contains(NextUnitIndex) == false)
	{
		Unit->SetUnitHandle(NextUnitIndex);
		return NextUnitIndex;
	}

	return InvalidUnitHandle;
}
