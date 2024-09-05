// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"
#include "ITT_State_SelectPick.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_State_SelectPick : public UITT_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

private:
	void SelectCharacter();

	UPROPERTY()
	TObjectPtr<class UITT_BasePlayer> OwnerUnit = nullptr;
	
	bool bAnySelected = false;
	TWeakObjectPtr<class UITT_Widget_Title> TitleWidget;
};
