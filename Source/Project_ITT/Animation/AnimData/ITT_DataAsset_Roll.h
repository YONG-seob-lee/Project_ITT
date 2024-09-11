// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_Define.h"
#include "ITT_DataAsset_Roll.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Roll : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData GroundPound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData PerfectJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData RollStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData RollStop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData RollToJog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData RollToWalk;
};
