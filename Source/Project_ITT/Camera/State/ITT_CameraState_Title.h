// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_CameraState.h"
#include "ITT_CameraState_Title.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CameraState_Title : public UITT_CameraState
{
	GENERATED_BODY()
public:
	UITT_CameraState_Title();
	virtual ~UITT_CameraState_Title() override;
	
	virtual void Initialize(uint8 Index, const FName& Name) override;
	virtual void Finalize() override;
	
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

protected:
	virtual void InitCamera() override;

private:
	void BeginCameraIdle();

private:
	TObjectPtr<class AITT_Actor_Camera> CharacterSelectCamera;
	
	TWeakObjectPtr<class UCapsuleComponent> CameraCapsuleComponent;

	bool bIdleCamera = false;
};
