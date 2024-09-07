// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ITT_TitleDefine.h"
#include "SubAnimInstance/ITT_SubAnimInstance.h"
#include "ITT_AnimInstance_Rose.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_ITT_API UITT_AnimInstance_Rose : public UITT_SubAnimInstance
{
	GENERATED_BODY()
public:
	void Initialize();
	void Finalize();

	void Select(EITT_SelectCharacter _SelectValue);	
private:
	UPROPERTY(Category = ITT_AnimInstance_Rose, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EITT_SelectCharacter SelectValue = EITT_SelectCharacter::None;
};
