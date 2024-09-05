// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"
#include "ITT_State_PlayerNormal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_State_PlayerNormal : public UITT_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

	void SetOnInteractionEventFunc(const TFunction<void()>& _Func) { OnInteractionCallback = _Func; }
	
private:
	void PlayerMove();
	
	void InteractionProcess();	
	
	void OnAxisUpDown(float AxisValue);
	void OnAxisLeftRight(float AxisValue);

	void OnClickInteraction();

	UPROPERTY()
	TObjectPtr<class UITT_BasePlayer> OwnerUnit = nullptr;

	UPROPERTY()
	TObjectPtr<class AITT_Actor_Camera> CameraActor = nullptr;

	float WalkSpeed = 0.f;
	float RunSpeed = 0.f;
	float SprintSpeed = 0.f;
	
	FVector2d JoyStickDistance = FVector2d::ZeroVector;
	FVector CachedUnitForward = FVector::ZeroVector;
	FVector CachedUnitRight = FVector::ZeroVector;

	TFunction<void()> OnInteractionCallback = nullptr;
};
