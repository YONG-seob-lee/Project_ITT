// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Actor_TrackCheckMachine.h"


// Sets default values
AITT_Actor_TrackCheckMachine::AITT_Actor_TrackCheckMachine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	if(SceneComponent)
	{
		RootComponent = SceneComponent;
	}

	NailCircuitComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NailCircuitComponent"));
}

// Called when the game starts or when spawned
void AITT_Actor_TrackCheckMachine::BeginPlay()
{
	Super::BeginPlay();

	for(const auto Component : this->GetComponents())
	{
		if(Component->ComponentHasTag(FName(TEXT("NailCircuit"))))
		{
			NailCircuitComponent = Cast<UStaticMeshComponent>(Component);
			break;
		}
	}

	if(NailCircuitComponent)
	{
		// UMaterialInterface* Material_01 = NailCircuitComponent->GetMaterial(static_cast<int32>(EITT_NailCircuitMaterial::Red));
		// UMaterialInterface* Material_02 = NailCircuitComponent->GetMaterial(static_cast<int32>(EITT_NailCircuitMaterial::Green));
		//
		// TArray<FMaterialParameterInfo> MaterialParameterInfos;
		// TArray<FGuid> OutParameterIds;

		NailCircuitComponent->SetScalarParameterValueOnMaterials(FName(TEXT("LightValue")), 0.f);
	}
	
}

// Called every frame
void AITT_Actor_TrackCheckMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bTurnLight == false)
	{
		return;
	}
	
	if(bRightOn_Red)
	{
		NailCircuitComponent->SetScalarParameterValueOnMaterials(FName(TEXT("LightValue_Red")), 100.f);
		bTurnLight = false;		
	}
	else
	{
		NailCircuitComponent->SetScalarParameterValueOnMaterials(FName(TEXT("LightValue_Red")), 0.f);
		bTurnLight = false;		
	}

	if(bRightOn_Green)
	{
		NailCircuitComponent->SetScalarParameterValueOnMaterials(FName(TEXT("LightValue_Green")), 100.f);
		bTurnLight = false;		
	}
	else
	{
		NailCircuitComponent->SetScalarParameterValueOnMaterials(FName(TEXT("LightValue_Green")), 0.f);
		bTurnLight = false;		
	}
}

