// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "ITT_MachineComponent_Rotate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITT_API UITT_MachineComponent_Rotate : public UITT_MachineComponentBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UITT_MachineComponent_Rotate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
