// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_BasePlayer.h"
#include "ITT_BasePlayer_Nail.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BasePlayer_Nail : public UITT_BasePlayer
{
	GENERATED_BODY()
public:
	void AttachNail(USkeletalMeshComponent* OuterMesh, const FName& SocketName) const;
	
	TObjectPtr<USkeletalMeshComponent> GetNailMesh() const;

};
