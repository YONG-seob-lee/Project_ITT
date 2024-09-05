// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Dash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_DataAsset_Dash : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseBlendspacesToMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashStop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashToJog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashToAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashFromLongJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData DashFromGroundPound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData DashToJogBS;
};
