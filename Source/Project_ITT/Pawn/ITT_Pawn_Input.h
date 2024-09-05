﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ITT_Pawn_Input.generated.h"

UCLASS()
class PROJECT_ITT_API AITT_Pawn_Input : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AITT_Pawn_Input();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool Create();
	void Destroy();
	
private:
	bool bIsCreated = false;
	
	UPROPERTY(Category = InputPawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputComponent> NewInputComponent = nullptr;
};
