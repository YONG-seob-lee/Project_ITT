// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_MachineComponentBase.h"

#include "ITT_Actor_Machine.h"


// Sets default values for this component's properties
UITT_MachineComponentBase::UITT_MachineComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UITT_MachineComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...	
	Machine = Cast<AITT_Actor_Machine>(GetOuter());

	if(!Machine)
	{
		return;
	}
}


// Called every frame
void UITT_MachineComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

