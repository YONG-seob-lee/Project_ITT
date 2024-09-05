// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Movement.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Movement : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUse180;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequencesData IdleAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseIdleGestures;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequencesData IdleGestures;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData BigGesturesStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData BigGesturesMH;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseActionIdle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequencesData ActionIdleAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData IdleToAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ActionToIdle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequencesData ExhaustedIdleAnimations;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData IdleToExhausted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ExhaustedToIdle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ActionIdleTriggerTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExhaustedIdleTriggerTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData StartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData StartInMotionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData StartInMotion_Var2_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData ActionStartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData ExhaustedStartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData StopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData GoToStopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ActionStopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ExhaustedStopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EasyStopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseMovementBlendSpace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequencesData MovementAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData MovementBlendSpace;
};
