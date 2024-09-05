// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AnimInstance/ITT_AnimInstance.h"
#include "ITT_AnimInstance_Doll.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_AnimInstance_Doll : public UITT_AnimInstance
{
	GENERATED_BODY()
public:
	void Initialize();
	void Finalize();

	void Select(float _SelectValue);
private:
	UPROPERTY(Category = ITT_AnimInstance_Doll, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SelectValue = 0.f;
};
