// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponent_Pendulum.h"

#include "ITT_Actor_Machine.h"
#include "PROJECT_ITT/ITT_InstUtil.h"


// Sets default values for this component's properties
UITT_MachineComponent_Pendulum::UITT_MachineComponent_Pendulum()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MachineAction = EITT_Machine_Action::Pendulum;
}


// Called when the game starts
void UITT_MachineComponent_Pendulum::BeginPlay()
{
	Super::BeginPlay();
	
	bStartMachine = true;
	PendulumDelegate = FTimerDelegate::CreateUObject(this, &UITT_MachineComponent_Pendulum::PendulumCallbackFunc);
}


// Called every frame
void UITT_MachineComponent_Pendulum::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	if(bStartMachine == false)
	{
		return;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float PendulumAngle = Machine->GetActorRotation().Roll;
	if(NextPendulumAngle == PendulumAngle::Max)
	{
		// 끝자락에 도달했을 때
		if(PendulumAngle == PendulumAngle::MaxRot )
		{
			bStartMachine = false;
			// 2초 정지 후 반대편 앵글로 이동				
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(PendulumHandler, PendulumDelegate, 2.f, false);		
		}
		else
		{
			Machine->AddActorLocalRotation(FRotator(0.f, 0.f, 1.f));
		}
	}
	else if(NextPendulumAngle == PendulumAngle::Min)
	{
		if(PendulumAngle == PendulumAngle::MinRot)
		{
			bStartMachine = false;
			// 2초 정지 후 반대편 앵글로 이동				
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(PendulumHandler, PendulumDelegate, 2.f, false);
		}
		else
		{
			Machine->AddActorLocalRotation(FRotator(0.f, 0.f, -1.f));
		}
	}
}

void UITT_MachineComponent_Pendulum::PendulumCallbackFunc()
{
	if(NextPendulumAngle == PendulumAngle::Max)
	{
		NextPendulumAngle = PendulumAngle::Min;
	}
	else if(NextPendulumAngle == PendulumAngle::Min)
	{
		NextPendulumAngle = PendulumAngle::Max;
	}

	bStartMachine = true;
}

