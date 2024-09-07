// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_Define.h"
#include "ITT_DataAsset_SelectDoll.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_SelectDoll : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SelectMh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData SelectTransition;
};
