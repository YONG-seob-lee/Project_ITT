// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MontageComponent.h"


UITT_MontageComponent::UITT_MontageComponent()
{
}

void UITT_MontageComponent::ClearCurrentMontagePool()
{
	if(AnimInstance == nullptr)
	{
		return;
	}

	if(AnimInstance->IsAnyMontagePlaying())
	{
		AnimInstance->Montage_Stop(0.f);
	}

	CurrentMontage.Empty();
	CurrentMontageName.Empty();
	CurrentMontageSectionName.Empty();
}

// Called every frame
void UITT_MontageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UITT_MontageComponent::SetAnimInstance(TObjectPtr<UAnimInstance> NewAnimInstance)
{
	if(AnimInstance == NewAnimInstance)
	{
		return;
	}

	ClearCurrentMontagePool();

	AnimInstance = NewAnimInstance;
}

void UITT_MontageComponent::BeginPlay()
{
	Super::BeginPlay(); 
}

