// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponent_PistonElevator.h"

#include "ITT_Actor_Machine.h"
#include "PROJECT_ITT/ITT_InstUtil.h"


// Sets default values for this component's properties
UITT_MachineComponent_PistonElevator::UITT_MachineComponent_PistonElevator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MachineAction = EITT_Machine_Action::PistonElevator;
}


// Called when the game starts
void UITT_MachineComponent_PistonElevator::BeginPlay()
{
	Super::BeginPlay();

	// ...

	bStartMachine = true;
	
	ElevatorDelegate = FTimerDelegate::CreateUObject(this, &UITT_MachineComponent_PistonElevator::ElevatorDownCallbackFunc);
}


// Called every frame
void UITT_MachineComponent_PistonElevator::TickComponent(float DeltaTime, ELevelTick TickType,
                                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// 머신이 사용 가능한지에 대한 여부
	if(bStartMachine == false)
	{
		return;
	}
	
	if(bOnHitHammer)
	{
		if(MachineLocation_Z == ElevatorVariable::ElevatorLength)
		{
			bOnHitHammer = false;
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(ElevatorHandler, ElevatorDelegate, 2.f, false);
			return;
		}
		
		if(MachineLocation_Z >= ElevatorVariable::ElevatorLength)
		{
			// 꼭대기에서 3초 정지 후 천천히 감소
			bOnHitHammer = false;
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(ElevatorHandler, ElevatorDelegate, 2.f, false);
		}

		const int32 RemainGap = static_cast<int32>(MachineLocation_Z) % static_cast<int32>(ElevatorVariable::UpperGap);
		if(RemainGap != 0)
		{
			MachineLocation_Z -= RemainGap;
		}

		MachineLocation_Z += ElevatorVariable::UpperGap;
		Machine->AddActorLocalTransform(FTransform(FVector(0.f, 0.f, ElevatorVariable::UpperGap)));
	}
	else
	{
		if(bMoveElevatorDown)
		{
			if(MachineLocation_Z <= 10.f)
			{
				bMoveElevatorDown = false;
			}
			MachineLocation_Z -= ElevatorVariable::DownperGap;
			Machine->AddActorLocalTransform(FTransform(FVector(0.f, 0.f, -ElevatorVariable::DownperGap)));
		}
	}

	ITT_LOG(TEXT("MachineLocation_Z = %f"), MachineLocation_Z);
}

void UITT_MachineComponent_PistonElevator::OnHitHammerCallbackFunc()
{
	if(bOnHitHammer == false)
	{
		bOnHitHammer = true;
		bMoveElevatorUpper = true;
	}
}

void UITT_MachineComponent_PistonElevator::ElevatorDownCallbackFunc()
{
	if(bMoveElevatorDown == false)
	{
		bMoveElevatorDown = true;
	}
}

