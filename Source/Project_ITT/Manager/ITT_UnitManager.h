// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "ITT_UnitManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_UnitManager : public UObject, public UITT_Singleton<UITT_UnitManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	TObjectPtr<class UITT_UnitBase> CreateUnit(int32 UnitTableId, TSubclassOf<UITT_UnitBase> UnitType, const FVector& Position = FVector::ZeroVector, const FRotator& Rotator = FRotator::ZeroRotator);

	TObjectPtr<class UITT_UnitBase> GetCurrentUnit();
	
	void DestroyUnit(ITT_Handle UnitHandle);
	void DestroyAllUnit();

	TObjectPtr<class AITT_CharacterBase> CreateCharacter(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot);

	TObjectPtr<UITT_UnitBase> GetUnit(ITT_Handle UnitHandle);
	ITT_Handle GetUnitHandle(TObjectPtr<UITT_UnitBase> UnitBase) const;
	
	TObjectPtr<AITT_CharacterBase> GetCharacterBase(ITT_Handle UnitHandle);
	ITT_Handle GetIsValidBasePlayer();

private:
	ITT_Handle MakeUnitHandle(const TObjectPtr<UITT_UnitBase> Unit) const;
	
	TMap<ITT_Handle, TObjectPtr<UITT_UnitBase>> Units;

	float LodScale = 1.f;
	bool bOutLineModeOn = true;
#define gUnitMng (*UITT_UnitManager::GetInstance())
};
