// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponent_MovingTrack.h"

#include "ITT_Actor_Machine.h"
#include "PROJECT_ITT/ITT_Define.h"


// Sets default values for this component's properties
UITT_MachineComponent_MovingTrack::UITT_MachineComponent_MovingTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	MachineAction = EITT_Machine_Action::MovingTrack;
}


// Called when the game starts
void UITT_MachineComponent_MovingTrack::BeginPlay()
{
	Super::BeginPlay();
	
	bStartMachine = true;
}


// Called every frame
void UITT_MachineComponent_MovingTrack::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	if(bActiveNail)
	{
		bOnHitNail = true;
		bMoveTrack = true;
		bActiveNail = false;
	}

	if(bActivePull)
	{
		bOnHitNail = false;
		bMoveTrack = true;
		bActivePull = false;
	}
	
	// 머신이 사용 가능한지에 대한 여부
	if(bStartMachine == false)
	{
		return;
	}
	
	if(bMoveTrack == false)
	{
		return;
	}
	
	if(bOnHitNail)
	{
		if(TrackLength <= 0.f)
		{
			bMoveTrack = false;
		}
		TrackLength -= TrackVariable::MovingGap;
		Machine->AddActorLocalTransform(FTransform(FVector(-TrackVariable::MovingGap, 0.f, 0.f)));
	}
	else
	{
		if(TrackLength <= 0.f)
		{
			bMoveTrack = false;
		}
		TrackLength -= TrackVariable::MovingGap;
		Machine->AddActorLocalTransform(FTransform(FVector(TrackVariable::MovingGap, 0.f, 0.f)));
	}

	ITT_LOG(TEXT("TrackLength : %f"), TrackLength);
}

void UITT_MachineComponent_MovingTrack::OnHitNailCallbackFunc()
{
	if(bOnHitNail == false)
	{
		bOnHitNail = true;
		bMoveTrack = true;
	}
}

void UITT_MachineComponent_MovingTrack::OnPullOutNailCallbackFunc()
{
	if(bOnHitNail)
	{
		bOnHitNail = false;
		bMoveTrack = true;
	}
}

