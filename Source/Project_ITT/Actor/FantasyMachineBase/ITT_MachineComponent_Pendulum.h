// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "ITT_MachineComponent_Pendulum.generated.h"


namespace PendulumAngle
{
	constexpr float MaxRot = 45.f;
	constexpr float MinRot = -45.f;

	const FString Max = TEXT("Max");
	const FString Min = TEXT("Min");
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MachineComponent_Pendulum : public UITT_MachineComponentBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UITT_MachineComponent_Pendulum();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void PendulumCallbackFunc();
	
	// PendulumAngle Variable
	FString NextPendulumAngle = PendulumAngle::Max;
	FTimerDelegate PendulumDelegate;
	FTimerHandle PendulumHandler;
};
