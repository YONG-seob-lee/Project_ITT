// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "ITT_MachineComponent_PistonElevator.generated.h"

namespace ElevatorVariable
{
	constexpr float ElevatorLength = 800.f;
	
	constexpr float UpperGap = 50.f;
	constexpr float DownperGap = 10.f;
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MachineComponent_PistonElevator : public UITT_MachineComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UITT_MachineComponent_PistonElevator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	// 해머가 히트됐을 때
	void OnHitHammerCallbackFunc();
	// 엘리베이터가 꼭대기에서 내려올 때
	void ElevatorDownCallbackFunc();

	UPROPERTY(VisibleAnywhere, Category= "HammerElevator", meta = (AllowPrivateAccess = "true"))
	float MachineLocation_Z = 0.f;

	UPROPERTY(EditAnywhere, Category= "HammerElevator", meta = (AllowPrivateAccess = "true"))
	bool bOnHitHammer = false;
	
	bool bMoveElevatorUpper = false;
	bool bMoveElevatorDown = false;

	FTimerDelegate ElevatorDelegate;
	FTimerHandle ElevatorHandler;

};
