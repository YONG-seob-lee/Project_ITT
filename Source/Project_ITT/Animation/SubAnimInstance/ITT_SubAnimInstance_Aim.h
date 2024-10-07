// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_SubAnimInstance.h"
#include "ITT_SubAnimInstance_Aim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SubAnimInstance_Aim : public UITT_SubAnimInstance
{
	GENERATED_BODY()

	FORCEINLINE void SetNailCount(int32 _NailCount) { NailCount = _NailCount; }
private:
	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 NailCount = 0;
};
