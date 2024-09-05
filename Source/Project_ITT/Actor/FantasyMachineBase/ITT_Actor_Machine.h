// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "GameFramework/Actor.h"
#include "ITT_Actor_Machine.generated.h"

UCLASS()
class PROJECT_ITT_API AITT_Actor_Machine : public AActor
{
	GENERATED_BODY()

public:
	AITT_Actor_Machine();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(Category = AITT_Actor_Machine, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
};
