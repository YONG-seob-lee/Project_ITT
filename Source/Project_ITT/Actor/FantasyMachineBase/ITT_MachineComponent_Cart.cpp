// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponent_Cart.h"

#include "ITT_Actor_Machine.h"
#include "PROJECT_ITT/ITT_InstUtil.h"


// Sets default values for this component's properties
UITT_MachineComponent_Cart::UITT_MachineComponent_Cart()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	MachineAction = EITT_Machine_Action::Cart;
}


// Called when the game starts
void UITT_MachineComponent_Cart::BeginPlay()
{
	Super::BeginPlay();
	
	bStartMachine = true;
	CartDelegate = FTimerDelegate::CreateUObject(this, &UITT_MachineComponent_Cart::TrackCallbackFunc);
}


// Called every frame
void UITT_MachineComponent_Cart::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	if(bStartMachine == false)
	{
		return;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(NextCartPosition == CartDirection::Finish)
	{
		if(CurrentPosition == CartDirection::CartLengthMax)
		{
			bStartMachine = false;
			// 2초 정지 후 반대편 트랙으로 이동				
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(CartHandler, CartDelegate, 2.f, false);	
		}
		{
			CurrentPosition += 4;
			Machine->AddActorLocalTransform(FTransform(FVector(0.f, 4.f, 0.f)));	
		}
	}
	else if(NextCartPosition == CartDirection::Start)
	{
		if(CurrentPosition == CartDirection::CartLengthMin)
		{
			bStartMachine = false;
			// 2초 정지 후 반대편 트랙으로 이동				
			UITT_InstUtil::GetGameWorld()->GetTimerManager().SetTimer(CartHandler, CartDelegate, 2.f, false);	
		}
		else
		{
			CurrentPosition -= 4;
			Machine->AddActorLocalTransform(FTransform(FVector(0.f, -4.f, 0.f)));	
		}
	}
}

void UITT_MachineComponent_Cart::TrackCallbackFunc()
{
	if(NextCartPosition == CartDirection::Finish)
	{
		NextCartPosition = CartDirection::Start;
	}
	else if(NextCartPosition == CartDirection::Start)
	{
		NextCartPosition = CartDirection::Finish;
	}

	bStartMachine = true;
}

