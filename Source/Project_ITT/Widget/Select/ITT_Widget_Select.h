// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Select.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Select : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Select"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;

	FORCEINLINE void BindChangeStorySceneFunc(const TFunction<void()>& _Func) { OnChangeStoryCallback = _Func; }
	
private:
	void InitScrollBox(TMap<int32, struct FSelectButton*>* ButtonDatas) const;
	
	TFunction<void()> OnChangeStoryCallback = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> CPP_SelectScrollBox = nullptr;
};

UCLASS()
class PROJECT_ITT_API UITT_Widget_SelectButton : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/Select/SelectButton_Widget.SelectButton_Widget'")); }

	virtual void NativeConstruct() override;
	
	void SetButtonData(const FString& ButtonName) const;
	void PlayAppearance();

	FORCEINLINE void SetOnClickSelectButtonFunc(const TFunction<void()>& _Function) { OnClickSelectButtonCallback =_Function; }

private:
	void OnClickButton();
	
	TFunction<void()> OnClickSelectButtonCallback = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_SelectButton> CPP_SelectButton = nullptr;
};