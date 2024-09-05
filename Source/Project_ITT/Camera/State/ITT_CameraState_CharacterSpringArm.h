// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_CameraState.h"
#include "ITT_CameraState_CharacterSpringArm.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CameraState_CharacterSpringArm : public UITT_CameraState
{
	GENERATED_BODY()

public:
	UITT_CameraState_CharacterSpringArm();
	virtual ~UITT_CameraState_CharacterSpringArm() override;
	
	virtual void Initialize(uint8 Index, const FName& Name) override;
	virtual void Finalize() override;
	
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

protected:
	virtual void InitCamera() override;
	
private:
	void ActorTickFunc(TObjectPtr<class UITT_UnitBase> Unit);

protected:
	TWeakObjectPtr<class AITT_CharacterBase> CharacterBase;
	
	UPROPERTY()
	TObjectPtr<class UCameraComponent> Cody_Camera;

	UPROPERTY()
	TObjectPtr<class UCameraComponent> May_Camera;
	
	TWeakObjectPtr<class UCapsuleComponent> Cody_CameraCapsuleComponent;
	
	FDelegateHandle ActorTickEvent;
};
