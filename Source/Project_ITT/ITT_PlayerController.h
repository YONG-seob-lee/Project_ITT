// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Define.h"
//#include "UINavController.h"
#include "ITT_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API AITT_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AITT_PlayerController();
	virtual ~AITT_PlayerController() override;
	
	virtual void CreateTouchInterface() override;
	virtual void ActivateTouchInterface(UTouchInterface* NewTouchInterface) override;

	FORCEINLINE TObjectPtr<UTouchInterface> GetCurrentTouchInterface() const { return CurrentTouchInterface; }
	class SITT_VirtualJoyStick* GetVirtualJoyStick() const;
	
	FORCEINLINE void SetJoyStickVisualCenter(FVector2d Center) { JoyStickVisualCenter = Center; }
	FORCEINLINE FVector2d SetJoyStickVisualCenter() const { return JoyStickVisualCenter; }

	FORCEINLINE ITT_Handle GetUnitHandle() const { return UnitHandle; }
	FORCEINLINE void SetUnitHandle(ITT_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE void ResetUnitHandle() { UnitHandle = InvalidUnitHandle; }

	virtual void OnPossess(APawn* InPawn) override;
	
private:
	ITT_Handle UnitHandle = InvalidUnitHandle;
	
	FVector2d JoyStickVisualCenter = FVector2d();
};
