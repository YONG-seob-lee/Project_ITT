// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Crouch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_DataAsset_Crouch : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseBlendspacesToMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseLookAt;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Mh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Stop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData Walk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterMh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterGroundPound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterSliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData EnterWalkSliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ExitMh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData ExitToMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData ExitToMovementBS;
};
