// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_BasePlayer.h"
#include "ITT_BasePlayer_Cody.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BasePlayer_Cody : public UITT_BasePlayer
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;
	
	void InitCamera();
private:
	
	void MakeNail(int32 HolsterIndex, FName SocketName);

	void SetAimed();
	void ThrowNail();
	
	void AttachHand(bool bAttachHand = true);
	int32 GetTargetNail(bool bFindEmpty);
	
	void ActorTickFunc(TObjectPtr<UITT_UnitBase> Unit);

	void NailTrace();

	TWeakObjectPtr<AITT_CharacterBase> CodyCharacterBase;

	TMap<int32, FName> HolsterSocket;
	
	// If 'true' state, Cody has the nail.
	UPROPERTY()
	TMap<int32, TObjectPtr<class UITT_BasePlayer_Nail>> HolsterNails;

	UPROPERTY()
	TObjectPtr<class UITT_BasePlayer_Nail> TargetNail = nullptr;
	
	UPROPERTY()
	TObjectPtr<class AITT_Actor_Camera> Cody_Camera;

	TWeakObjectPtr<class UCapsuleComponent> Cody_CameraCapsuleComponent;
	
	UPROPERTY()
	TObjectPtr<class AITT_Actor_Camera> Aim_Camera;

	UPROPERTY()
	TObjectPtr<class UITT_Widget_Aimed> AimWidget = nullptr;

	FVector ShootDirection = FVector::Zero();
	FDelegateHandle ActorTickEvent;
	bool bAimed = false;
};
