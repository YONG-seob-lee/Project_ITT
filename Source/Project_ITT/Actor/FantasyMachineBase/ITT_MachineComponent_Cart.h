// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_MachineComponentBase.h"
#include "ITT_MachineComponent_Cart.generated.h"


namespace CartDirection
{
	constexpr int32 CartLengthMax = 1300;
	constexpr int32 CartLengthMin = 0;

	const FString Start = TEXT("Start");
	const FString Finish = TEXT("Finish");
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_MachineComponent_Cart : public UITT_MachineComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UITT_MachineComponent_Cart();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	void TrackCallbackFunc();
	
	// Cart Variable
	FString NextCartPosition = CartDirection::Finish;

	UPROPERTY(EditAnywhere, Category= "CartPosition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentPosition = 0;
	
	FTimerDelegate CartDelegate;
	FTimerHandle CartHandler;
};
