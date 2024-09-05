// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Landing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_DataAsset_Landing : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseOnlyBasicLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseBlendspacesToMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Landing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData LandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData LandingHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData LandingHighFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData CancelLandingHighFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashLandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData PerfectDashLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData PerfectDashLandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData StartFromStill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DelayedStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData StartFromStillHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DelayedStartHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SkyDiveLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SkyDiveLandingFwd;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData LandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData LandingHighFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData DashLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData PerfectDashLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData SkyDiveLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData StartFromStillBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData DelayedStartBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData StartFromStillHighBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData DelayedStartHighBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_StartFromStill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_DelayedStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_StartFromStillHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_DelayedStartHigh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_CancelLandingHighFwd;
};
