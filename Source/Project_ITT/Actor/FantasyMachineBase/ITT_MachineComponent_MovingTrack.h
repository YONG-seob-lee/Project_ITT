// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "ITT_MachineComponent_MovingTrack.generated.h"

namespace TrackVariable
{
	constexpr float TrackLength = 1000.f;
	constexpr float MovingGap = 50.f;
}



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MachineComponent_MovingTrack : public UITT_MachineComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UITT_MachineComponent_MovingTrack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OnHitNailCallbackFunc();
	void OnPullOutNailCallbackFunc();

	float TrackLength = 1000.f;

	bool bMoveTrack = false;
	bool bOnHitNail = false;
	
	UPROPERTY(EditAnywhere, Category= "TrackPosition", meta = (AllowPrivateAccess = "true"))
	bool bActiveNail = false;

	UPROPERTY(EditAnywhere, Category= "TrackPosition", meta = (AllowPrivateAccess = "true"))
	bool bActivePull = false;
};
