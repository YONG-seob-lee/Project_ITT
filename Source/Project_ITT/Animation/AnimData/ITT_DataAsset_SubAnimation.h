// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ITT_Define.h"
#include "ITT_DataAsset_SubAnimation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ITT_API UITT_DataAsset_SubAnimation : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UITT_SubAnimInstance> SubAnimInstanceClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bReInitAnimWhenRequested;
};
