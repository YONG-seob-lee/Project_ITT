// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_SubAnimInstance.h"
#include "ITT_SubAnimInstance_Movement.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SubAnimInstance_Movement : public UITT_SubAnimInstance
{
	GENERATED_BODY()

public:
	UITT_SubAnimInstance_Movement();

	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;
	virtual void NativeBeginPlay() override;
};
