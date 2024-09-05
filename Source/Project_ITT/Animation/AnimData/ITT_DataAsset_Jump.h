// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Jump.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Jump : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  bool UseBasicJumpOnly;
	
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Falling;
	
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpWithSpeedBoost;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpFromLanding;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpFromLandingHigh;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpFwd;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpFwdWithSpeedBoost;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequencesData JumpFwdFromLanding;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequencesData JumpFwdFromLanding_Var2;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData JumpFwdFromLandingHigh;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData Jump180L;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData Jump180R;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData DashJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData DashStopJump;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData PerfectDashJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITT_AnimSequenceData PerfectDashStopJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLanding_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLanding_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLandingHigh_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLandingHigh_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLandingHigh_Blend;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLandingHigh_Blend;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float Jump180_Blend;
};
