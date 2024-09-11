// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "PROJECT_ITT/Data/ITT_TitleDefine.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Character_UnSelect.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_ITT_API UITT_Widget_Character_Selected : public UITT_Widget
{
	GENERATED_BODY()
public:
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Bg = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Name = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> CPP_JoyStickSwitcher = nullptr;
};

UCLASS()
class PROJECT_ITT_API UITT_Widget_Character_UnSelect : public UITT_Widget
{
	GENERATED_BODY()
	
public:
	void SetBgColor(FLinearColor _Color);
	void SetJoyStick(int32 JoyStickIndex);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Bg = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Name = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> CPP_JoyStickSwitcher = nullptr;
};

UCLASS()
class PROJECT_ITT_API UITT_Widget_Choose_Character : public UITT_Widget
 {
	GENERATED_BODY()
public:
	
	static FName GetWidgetName() { return TEXT("ChooseCharacter"); }

	virtual void NativeConstruct() override;
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;

	void RefreshCharacterState(ITT_Player Player, EITT_SelectCharacter NextPosition);
	void SelectCharacterState(ECommonInputType CommonInput) const;

private:

	EITT_SelectCharacter FirstPlayerCurrentPos;
	EITT_SelectCharacter SecondPlayerCurrentPos;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_Widget_Character_UnSelect> CPP_1P = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_Widget_Character_UnSelect> CPP_2P = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_Widget_Character_Selected> CPP_MaySelected = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_Widget_Character_Selected> CPP_CodySelected = nullptr;
};