// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Title.h"

#include "ITT_InstUtil.h"
#include "ITT_Widget_Character_UnSelect.h"
#include "Manager/ITT_InputManager.h"

void UITT_Widget_Title::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	gInputMng.GetOnInputMethodChange().AddUObject(this, &UITT_Widget_Title::OnInputMethodChange);
}

void UITT_Widget_Title::FinishWidget()
{
	gInputMng.GetOnInputMethodChange().RemoveAll(this);
	Super::FinishWidget();
}

void UITT_Widget_Title::RefreshCharacterState(ITT_Player Player, EITT_SelectCharacter NextPosition) const
{
	CPP_ChooseCharacter->RefreshCharacterState(Player, NextPosition);
}

void UITT_Widget_Title::SelectState(bool bSelectCharacter /* = false */, bool bSelectJoyStick /* = false */)
{
	//CPP_ChooseCharacter->SelectCharacterState(bSelectCharacter, bSelectJoyStick);
}

void UITT_Widget_Title::OnInputMethodChange(ECommonInputType CommonInput)
{
	CPP_ChooseCharacter->SelectCharacterState(CommonInput);
}
