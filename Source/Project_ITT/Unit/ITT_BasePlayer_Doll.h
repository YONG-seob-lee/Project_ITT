﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_BasePlayer.h"
#include "ITT_BasePlayer_Doll.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BasePlayer_Doll : public UITT_BasePlayer
{
	GENERATED_BODY()
public:
	TObjectPtr<USkeletalMeshComponent> GetSkeletalMeshComponent() const;
};
