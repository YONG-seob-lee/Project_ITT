// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ITT_AnimNotify_ThrowEnd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_AnimNotify_ThrowEnd : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
