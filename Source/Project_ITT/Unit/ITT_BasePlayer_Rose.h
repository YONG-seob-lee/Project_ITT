// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_BasePlayer.h"
#include "Animation/ITT_AnimInstance_Doll.h"
#include "ITT_BasePlayer_Rose.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BasePlayer_Rose : public UITT_BasePlayer
{
	GENERATED_BODY()

public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot) override;
	virtual void DestroyUnit() override;

	void SetDollAnimInst(const TObjectPtr<UITT_AnimInstance_Doll>& MayDollInst, const TObjectPtr<UITT_AnimInstance_Doll>& CodyDollInst);

	TWeakObjectPtr<UITT_AnimInstance_Doll> GetDollAnimInstance(int32 DollIndex /* May = 0, Cody = 1 */);
private:
	TWeakObjectPtr<UITT_AnimInstance_Doll> MayDollAnim;
	TWeakObjectPtr<UITT_AnimInstance_Doll> CodyDollAnim;
};
