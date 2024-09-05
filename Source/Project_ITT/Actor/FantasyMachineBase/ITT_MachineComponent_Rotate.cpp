// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponent_Rotate.h"

#include "ITT_Actor_Machine.h"


// Sets default values for this component's properties
UITT_MachineComponent_Rotate::UITT_MachineComponent_Rotate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MachineAction = EITT_Machine_Action::Rotate;
}


// Called when the game starts
void UITT_MachineComponent_Rotate::BeginPlay()
{
	Super::BeginPlay();

	bStartMachine = true;
}


// Called every frame
void UITT_MachineComponent_Rotate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(bStartMachine == false)
	{
		return;
	}

	Machine->AddActorLocalRotation(FRotator(0.f, 0.f, 1.f));
}

