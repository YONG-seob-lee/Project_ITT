// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterState/ITT_CharacterState.h"
#include "ITTAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UITTAnimInstance();
	virtual ~UITTAnimInstance() override;

	UFUNCTION(BlueprintPure, Category = "Anim", meta = (BlueprintThreadSafe))
	static class UAnimSequenceBase* GetRandomAnimAnimSequence(const FITT_AnimSequencesData& AnimSequencesData);

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;
	virtual void NativeBeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void LinkSubAnimation();
private:
	TSubclassOf<UAnimInstance> GetSubAnimInstanceClass(EITT_CharacterState _CharacterState);
	
	TWeakObjectPtr<class AITT_CharacterBase> CharacterBase;

	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EITT_CharacterState PreCharacterState;
	
	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EITT_CharacterState CharacterState;

	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EITT_CharacterState, TObjectPtr<class UITT_DataAsset_SubAnimation>> CharacterStateToAnimationData;
};
