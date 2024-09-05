﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITT_MontageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UITT_MontageComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetAnimInstance(TObjectPtr<UAnimInstance> NewAnimInstance);
protected:
	virtual void BeginPlay() override;

private:
	void ClearCurrentMontagePool();
	
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance = nullptr;

	UPROPERTY(Category = UITT_MontageComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> CurrentMontage;

	TArray<FName> CurrentMontageName;
	TArray<FName> CurrentMontageSectionName;
};
