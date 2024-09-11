// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "PROJECT_ITT/Data/ITT_TitleDefine.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Title.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_ITT_API UITT_Widget_Title : public UITT_Widget
{
	GENERATED_BODY()

public:
	FORCEINLINE static FName GetWidgetName() {return TEXT("Title"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;
	
	void RefreshCharacterState(ITT_Player Player, EITT_SelectCharacter NextPosition) const;
	void SelectState(bool bSelectCharacter = false, bool bSelectJoyStick = false);

private:
	void OnInputMethodChange(ECommonInputType CommonInput);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UITT_Widget_Choose_Character> CPP_ChooseCharacter = nullptr;
};
