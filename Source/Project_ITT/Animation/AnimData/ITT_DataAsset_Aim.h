// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_DataAsset_SubAnimation.h"
#include "ITT_Define.h"
#include "ITT_DataAsset_Aim.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_Aim : public UITT_DataAsset_SubAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpaceData AimJogAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_mh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog_Bwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog_Bwd_Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog_Bwd_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog_Fwd_Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aim_Jog_Fwd_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FITT_AnimSequenceData Throw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Throw_Last;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Equip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aquire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequenceData Aquire_Aim;
};
