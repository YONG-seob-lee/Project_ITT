// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTAnimInstance.h"

#include "AnimData/ITT_DataAsset_SubAnimation.h"
#include "Character/ITT_CharacterBase.h"
#include "SubAnimInstance/ITT_SubAnimInstance.h"
#include "SubAnimInstance/ITT_SubAnimInstance_Aim.h"

UITTAnimInstance::UITTAnimInstance()
{
}

UITTAnimInstance::~UITTAnimInstance()
{
}

UAnimSequenceBase* UITTAnimInstance::GetRandomAnimAnimSequence(const FITT_AnimSequencesData& AnimSequencesData)
{
	if (AnimSequencesData.AnimSequences.Num() == 0)
	{
		return nullptr;
	}
	
	float totalProbability = 0.f;
	
	for (auto& Sequence : AnimSequencesData.AnimSequences)
	{
		totalProbability += Sequence.Probability;
	}

	float randomVal = FMath::RandRange(0.f, totalProbability);
	for (auto& Sequence : AnimSequencesData.AnimSequences)
	{
		randomVal -= Sequence.Probability;

		if (randomVal <= 0.f)
		{
			return Sequence.ObjectPtr;
		}
	}

	return AnimSequencesData.AnimSequences[0].ObjectPtr;
}

void UITTAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (GetOwningActor())
	{
		CharacterBase = Cast<AITT_CharacterBase>(GetOwningActor());

		if (CharacterBase != nullptr)
		{
			CharacterStateToAnimationData = CharacterBase->GetCharacterStateToAnimationData();
		}
	}
}

void UITTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterBase != nullptr)
	{
		if (CharacterState != CharacterBase->GetCharacterState())
		{
			PreCharacterState = CharacterState;
			CharacterState = CharacterBase->GetCharacterState();
		}
	}
}

void UITTAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UITTAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UITTAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UITTAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UITTAnimInstance::LinkSubAnimation()
{
	if(const TSubclassOf<UAnimInstance> SubAnimInstance = GetSubAnimInstanceClass(CharacterState))
	{
		LinkAnimClassLayers(SubAnimInstance);
	}
}

TSubclassOf<UAnimInstance> UITTAnimInstance::GetSubAnimInstanceClass(EITT_CharacterState _CharacterState)
{
	if(const TObjectPtr<UITT_DataAsset_SubAnimation>* SubAnimation = CharacterStateToAnimationData.Find(_CharacterState))
	{
		return SubAnimation->GetClass();
	}

	return nullptr;
}
