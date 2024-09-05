// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Actor_Machine.h"
#include "ITT_Actor_TrackCheckMachine.generated.h"

UENUM()
enum class EITT_NailCircuitMaterial : uint32
{
	None = 0,
	Red = 1,
	Green = 2,
};

UCLASS()
class PROJECT_ITT_API AITT_Actor_TrackCheckMachine : public AITT_Actor_Machine
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AITT_Actor_TrackCheckMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> NailCircuitComponent = nullptr;

	UPROPERTY(EditAnywhere, Category= "TrackCheckMachine", meta = (AllowPrivateAccess = "true"))
	bool bTurnLight = false;
	
	UPROPERTY(EditAnywhere, Category= "TrackCheckMachine", meta = (AllowPrivateAccess = "true"))
	bool bRightOn_Red = false;

	UPROPERTY(EditAnywhere, Category= "TrackCheckMachine", meta = (AllowPrivateAccess = "true"))
	bool bRightOn_Green = false;
};
