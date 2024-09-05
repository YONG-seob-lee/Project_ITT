// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Manager/Tool/InputTouch/ITT_PreTouchProcessor.h"
#include "UObject/Object.h"
#include "ITT_BuiltInWidgetTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_BuiltInWidgetTool : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TSharedPtr<class FITT_PreTouchProcessor> GetPreTouchProcessor() const { return PreTouchProcessor; }
	FORCEINLINE TObjectPtr<class UITT_Widget_DialogScreenFader> GetDialogScreenFader() const { return DialogScreenFader;}
	FORCEINLINE TObjectPtr<class UITT_Widget_Toast> GetToastWidget() const { return ToastWidget; }
	FORCEINLINE TObjectPtr<class UITT_Widget_Loading> GetLoadingWidget() const { return LoadingWidget; }
	
	void BuiltInitialize();
	void Initialize();
	void Finalize();
	void Tick(float DeltaTime);

	void UpdatePreTouchProcessor() const;
	
private:
	
	TSharedPtr<FITT_PreTouchProcessor> PreTouchProcessor;
	
	UPROPERTY()
	TObjectPtr<UITT_Widget_DialogScreenFader> DialogScreenFader = nullptr;

	UPROPERTY()
	TObjectPtr<UITT_Widget_Toast> ToastWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UITT_Widget_Loading> LoadingWidget = nullptr;
};
