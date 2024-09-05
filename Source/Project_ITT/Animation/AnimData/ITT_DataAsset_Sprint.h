// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_DataAsset_Sprint.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Sprint : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SprintStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SprintFromLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData Sprint;
};
