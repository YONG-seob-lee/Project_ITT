// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_UnitBase.h"
#include "ITT_BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BasePlayer : public UITT_UnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot) override;
	virtual void DestroyUnit() override;

	bool CreatePlayerStateMachine();
	
	void SetSelfPlayer(bool _bSelfPlayer);
	void ChangePlayerState(EITT_UnitState UnitState) const;
	void SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const;

	void SetActorEnableCollision(bool bUnitEnableCollision) const;
	void ClearComponentOverlaps() const;

	void SetActionState(EITT_UnitActionState _ActionState) const;
	
	void SetMoveSpeed(float MoveSpeed) const;

	bool DoesSocketExist(const FName& Socket) const;
	void AttachMeshToSocket(const FName& SocketName, const TObjectPtr<class UITT_BasePlayer_Doll>& Doll);

protected:
	virtual void ChangeActionState(EITT_UnitActionState ActionType) const override;
	
	bool bSelfPlayer = false;

private:
	UPROPERTY()
	TObjectPtr<UITT_StateMachine> PlayerStateMachine = nullptr;
};
