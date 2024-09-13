// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "PROJECT_ITT/StateMachine/ITT_StateMachine.h"
#include "UObject/Object.h"
#include "ITT_UnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_UnitBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void Tick(float DeltaTime);
	
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos = FVector::ZeroVector, const FRotator& Rot = FRotator::ZeroRotator);
	virtual void DestroyUnit();

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const;
	void SetUnitPosition(const FVector& NewSpawnUnitPosition) const;
	
	FORCEINLINE void SetUnitHandle(ITT_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE ITT_Handle GetUnitHandle() const { return UnitHandle; }
	
	FORCEINLINE struct FResource_Unit* GetResourceUnitData() const { return ResourceUnitData; }

	TObjectPtr<UAnimInstance> GetAnimInstance() const;
	
	FORCEINLINE TObjectPtr<AITT_CharacterBase> GetCharacterBase() const { return CharacterBase.Get(); }
	FORCEINLINE FVector GetCharacterLocation() const { return CharacterBase->GetCurrentLocation(); }

	float GetMovingSpeed() const;
	
	FITT_UnitActorTickDelegate OnActorTickDelegate;

	FORCEINLINE ITT_Character GetUnitTableId() { return static_cast<ITT_Character>(ResourceUnitTableId); }
protected:
	bool CreateActionStateMachine();
	void DestroyActionStateMachine();
	void AddActionState(EITT_UnitActionState State, const FName& Name, TSubclassOf<class UITT_StateBase> ClassType);
	FORCEINLINE TObjectPtr<UITT_StateBase> GetActionState(EITT_UnitActionState State) const { return ActionStateMachine->GetState(static_cast<uint8>(State)); }

	virtual void ChangeActionState(EITT_UnitActionState ActionType) const;

	TObjectPtr<UActorComponent> GetActorComponentByTag(TSubclassOf<UActorComponent> ClassType, FName TabName, bool bIncludeFromChildActors = false) const;
	
	TWeakObjectPtr<AITT_CharacterBase> CharacterBase = nullptr;
private:
	FORCEINLINE bool IsValidCharacterActor() const { return CharacterBase.IsValid(); }

	ITT_Handle UnitHandle = InvalidUnitHandle;
	
	int32 ResourceUnitTableId = INDEX_NONE;
	FResource_Unit* ResourceUnitData = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UITT_StateMachine> ActionStateMachine = nullptr;
};
