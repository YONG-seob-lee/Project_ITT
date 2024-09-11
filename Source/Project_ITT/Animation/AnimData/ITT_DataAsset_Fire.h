// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_Define.h"
#include "ITT_DataAsset_Fire.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Fire : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FITT_AnimSequenceData Throw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Throw_Last;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Equip;
};
