// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ITT_Button.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Button : public UCommonButtonBase
{
	GENERATED_BODY()
	public:
	UITT_Button();
	virtual ~UITT_Button() override;
	virtual void NativeConstruct() override;
	
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual const FText GetPaletteCategory() override;

	void SetOnClickedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnClickedDelegate = Delegate; }
	FORCEINLINE void UnbindClickedDelegate() { ITT_OnClickedDelegate.Clear(); }
	void SetOnPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnPressedDelegate = Delegate; }
	FORCEINLINE void UnbindPressedDelegate() { ITT_OnPressedDelegate.Clear(); }
	void SetOnReleasedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnReleasedDelegate = Delegate; }
	FORCEINLINE void UnbindReleasedDelegate() { ITT_OnReleasedDelegate.Clear(); }
	void SetOnHoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnHoveredDelegate = Delegate; }
	FORCEINLINE void UnbindHoveredDelegate() { ITT_OnHoveredDelegate.Clear(); }
	void SetOnUnhoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnUnhoveredDelegate = Delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { ITT_OnUnhoveredDelegate.Clear(); }
	void SetWillCloseWidgetDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_WillCloseWidgetDelegate = Delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { ITT_WillCloseWidgetDelegate.Clear(); }
	void SetWillCreateSceneDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_WillCreateSceneDelegate = Delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { ITT_WillCreateSceneDelegate.Clear(); }
	void SetPlayAnimDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_PlayAnimDelegate = Delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { ITT_PlayAnimDelegate.Clear(); }
	void SetOnClickedInDelayTimeDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnClickedInDelayTimeDelegate = Delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { ITT_OnClickedInDelayTimeDelegate.Clear(); }
	void SetOnLongPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); ITT_OnLongPressedDelegate = Delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { ITT_OnLongPressedDelegate.Clear(); }

	FORCEINLINE void SetCustomVector(const FVector& Vector) { CustomVector = Vector;}
	FORCEINLINE FVector GetCustomVector() const { return CustomVector; }
	
private:
	void SetDelegates();
	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnRelease();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnhover();

	FORCEINLINE bool IsUseClockedDelay() const { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() const { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
	
protected:	
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseClickedDelay = false;
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseClickedDelay"))
	float ClickedDelayTime = 0.f;
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseReleasedDelay = false;
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseReleasedDelay"))
	float ReleasedDelayTime = 0.f;
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseLongPressedEvent = false;
	UPROPERTY(Category = UITT_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseLongPressedEvent"))
	float LongPressedTime = 0.f;
	
	FCommonButtonEvent ITT_OnClickedDelegate;
	FCommonButtonEvent ITT_OnPressedDelegate;
	FCommonButtonEvent ITT_OnReleasedDelegate;
	FCommonButtonEvent ITT_OnHoveredDelegate;
	FCommonButtonEvent ITT_OnUnhoveredDelegate;

	FCommonButtonEvent ITT_OnClickedInDelayTimeDelegate;
	FCommonButtonEvent ITT_OnLongPressedDelegate;

	FCommonButtonEvent ITT_PlayAnimDelegate;
	FCommonButtonEvent ITT_WillCloseWidgetDelegate;
	FCommonButtonEvent ITT_WillCreateSceneDelegate;

	FTimerHandle PressTimerHandle;
	
	float LastClickedTime = 0.f;
	float LastReleasedTime = 0.f;

	FVector CustomVector = FVector::ZeroVector;
};
