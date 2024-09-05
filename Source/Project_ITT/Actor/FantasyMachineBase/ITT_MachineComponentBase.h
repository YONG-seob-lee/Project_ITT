// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITT_MachineComponentBase.generated.h"


UENUM()
enum EITT_Machine_Action : uint32
{
	None = 0,
	Rotate,
	Pendulum,
	Cart,
	MovingTrack,
	PistonElevator,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MachineComponentBase : public UActorComponent
{
	GENERATED_BODY()
public:	
	UITT_MachineComponentBase();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
		
	EITT_Machine_Action MachineAction = EITT_Machine_Action::None;
	
	UPROPERTY()
	TObjectPtr<class AITT_Actor_Machine> Machine = nullptr;

	bool bStartMachine = false;
};
