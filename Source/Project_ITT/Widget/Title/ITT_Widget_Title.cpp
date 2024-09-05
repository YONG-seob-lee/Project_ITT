// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Title.h"

#include "ITT_Widget_Character_UnSelect.h"

void UITT_Widget_Title::RefreshCharacterState(ITT_Player Player, EITT_SelectCharacter NextPosition) const
{
	CPP_ChooseCharacter->RefreshCharacterState(Player, NextPosition);
}

void UITT_Widget_Title::SelectState(bool bSelectCharacter /* = false */, bool bSelectJoyStick /* = false */)
{
	CPP_ChooseCharacter->SelectCharacterState(bSelectCharacter, bSelectJoyStick);
}