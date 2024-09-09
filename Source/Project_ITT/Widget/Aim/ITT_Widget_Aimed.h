// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ITT_Widget.h"
#include "ITT_Widget_Aimed.generated.h"

UCLASS()
class PROJECT_ITT_API UITT_Widget_Nail : public UITT_Widget
{
	GENERATED_BODY()
public:
	void FallOutNail(bool bFailOut = true);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Full = nullptr;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> ReturnNail = nullptr;
};
/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Aimed : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/Widgets/Aim/AimWidget.AimWidget")); }
	
	virtual void NativeConstruct() override;
	
	void NailMovement(int32 NailIndex, bool bThrowNail = true);
	
private:
	TMap<int32, TObjectPtr<class UITT_Widget_Nail>> NailCount;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UITT_Widget_Nail> CPP_Nail_01 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UITT_Widget_Nail> CPP_Nail_02 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UITT_Widget_Nail> CPP_Nail_03 = nullptr;
};