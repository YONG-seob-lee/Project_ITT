// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ITT_Define.h"
#include "ITT_SubAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SubAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UITT_SubAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void SetAnimDataAsset(const TObjectPtr<class UITT_DataAsset_SubAnimation>& _AnimDataAsset) { AnimDataAsset = _AnimDataAsset; }
	
protected:
	TWeakObjectPtr<class AITT_CharacterBase> CharacterBase;
	TWeakObjectPtr<class UCharacterMovementComponent> CharacterMovement;

	UPROPERTY(Category = ITTAnim, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UITT_DataAsset_SubAnimation> AnimDataAsset;

	UPROPERTY(Category = ITTAnim, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EITT_CharacterState PreCharacterState;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	
	// -- Speed -- //
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector Velocity;
	
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float GroundSpeedPerMaxJogSpeed;
	
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MinSpeed;
	
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed;

	
	// -- Direction -- //
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator ControlRotation;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator ActorRotation;
	
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector ForwardVector;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float FaceYaw_Cached;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float FaceYaw_Target;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float FaceYaw;
};
