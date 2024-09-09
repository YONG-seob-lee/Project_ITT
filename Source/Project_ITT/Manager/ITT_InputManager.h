// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "ITT_InputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_InputManager : public UObject, public UITT_Singleton<UITT_InputManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	void RegistAxis(EITT_Axis_Type AxisType, EITT_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event);
	void RegistAxis_Select(EITT_Axis_Type AxisType, EITT_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event);
	
	void RegistTouch(EITT_Touch_Event TouchEventType, const FInputTouchBinding& Event);
	void RegistAndroidButton(EITT_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate);
	
	void RegistInteractionButton(const FSimpleDelegate& Delegate);
	void RegistSelectCharacterButton(const FSimpleDelegate& Delegate);
	
	void CreateInputPawn();
	void DestroyInputPawn();

	FORCEINLINE FBindAllKeysDelegate& GetBindAllKeysDelegate() { return AllKeysDelegate; }
	FORCEINLINE FBindSelectDelegate& GetBindSelectDelegate() { return OnSelectDollDelegate; }
	FORCEINLINE FBindPickDelegate& GetBindPickDollDelegate() { return OnPickDollDelegate; }
	FORCEINLINE FBindFireDelegate GetBindFireDelegate() { return OnFireDelegate; }
	FORCEINLINE FBindAimedDelegate& GetBindAimedDelegate() { return OnAimedDelegate; }
	
private:
	UPROPERTY()
	TObjectPtr<class AITT_Pawn_Input> InputPawn = nullptr;

	FBindAllKeysDelegate AllKeysDelegate;
	FBindSelectDelegate OnSelectDollDelegate;
	FBindPickDelegate OnPickDollDelegate;
	FBindAimedDelegate OnAimedDelegate;
	FBindFireDelegate OnFireDelegate;
	
	// todo : 용섭 Input Mapping Part
	
public:
	void LeftAxisUpDown(float Value);
	void LeftAxisLeftRight(float Value);
	void RightAxisUpDown(float Value);
	void RightAxisLeftRight(float Value);

	void LeftAxis_Select(float Value);
	
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location);
	void AndroidBack();
	void AndroidMenu();

	void Interaction();

private:
	FInputAxisBinding CharacterMove_UpDownEvent = FInputAxisBinding(TEXT("CharacterMove_UpDown"));
	FInputAxisBinding CharacterMove_LeftRightEvent = FInputAxisBinding(TEXT("CharacterMove_LeftRight"));
	
	FInputAxisBinding CameraMove_UpDownEvent = FInputAxisBinding(TEXT("CameraMove_UpDown"));
	FInputAxisBinding CameraMove_LeftRightEvent = FInputAxisBinding(TEXT("CameraMove_LeftRight"));

	FInputAxisBinding SelectMove_Event = FInputAxisBinding(TEXT("SelectMove_Event"));
	
	FInputTouchBinding TouchDownEvent = FInputTouchBinding(IE_Pressed);
	FInputTouchBinding TouchUpEvent = FInputTouchBinding(IE_Released);
	FInputTouchBinding TouchMoveEvent = FInputTouchBinding(IE_Repeat);
	FSimpleDelegate AndroidBackDelegate;
	FSimpleDelegate AndroidMenuDelegate;

	FSimpleDelegate InteractionDelegate;
	FSimpleDelegate SelectCharacterButton;

	
#define gInputMng (*UITT_InputManager::GetInstance())
};
