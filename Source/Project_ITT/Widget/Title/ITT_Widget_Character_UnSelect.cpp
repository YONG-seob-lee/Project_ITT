// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Character_UnSelect.h"

#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

namespace ChooseAnimation
{
	const FName F_Player_Select_Cody = TEXT("1p_Select_Cody");
	const FName F_Player_Select_May = TEXT("1p_Select_May");
	const FName F_Player_UnSelect_Cody = TEXT("1p_UnSelect_Cody");
	const FName F_Player_UnSelect_May = TEXT("1p_UnSelect_May");
	const FName S_Player_Select_Cody = TEXT("2p_Select_Cody");
	const FName S_Player_Select_May = TEXT("2p_Select_May");
	const FName S_Player_UnSelect_Cody = TEXT("2p_UnSelect_Cody");
	const FName S_Player_UnSelect_May = TEXT("2p_UnSelect_May");
}

void UITT_Widget_Character_UnSelect::SetBgColor(FLinearColor _Color)
{
	CPP_Bg->SetBrushTintColor(FSlateColor(_Color));
}

void UITT_Widget_Character_UnSelect::SetJoyStick(int32 JoyStickIndex)
{
	CPP_JoyStickSwitcher->SetActiveWidgetIndex(JoyStickIndex);
}

void UITT_Widget_Choose_Character::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_1P->SetBgColor(FLinearColor(1.0f, 0.239583f, 0.239583f, 1.f));
	CPP_2P->SetBgColor(FLinearColor(0.206075f, 0.312894f, 1.f, 1.f));
	
	CPP_MaySelected->SetVisibility(ESlateVisibility::Collapsed);
	CPP_CodySelected->SetVisibility(ESlateVisibility::Collapsed);

	CPP_1P->SetVisibility(ESlateVisibility::HitTestInvisible);
	CPP_2P->SetVisibility(ESlateVisibility::HitTestInvisible);

	FillDefaultAnimations();

	FirstPlayerCurrentPos = EITT_SelectCharacter::None;
	SecondPlayerCurrentPos = EITT_SelectCharacter::None;
}

void UITT_Widget_Choose_Character::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UITT_Widget_Choose_Character::RefreshCharacterState(ITT_Player Player, EITT_SelectCharacter NextPosition)
{	
	if(Player == ITT_Player::First)
	{
		if(FirstPlayerCurrentPos == EITT_SelectCharacter::May && NextPosition == EITT_SelectCharacter::None)
		{
			PlayAnimationByName(ChooseAnimation::F_Player_UnSelect_May);
			FirstPlayerCurrentPos = EITT_SelectCharacter::None;
			return;
		}
		
		if(FirstPlayerCurrentPos == EITT_SelectCharacter::None)
		{
			if(NextPosition == EITT_SelectCharacter::May)
			{
				PlayAnimationByName(ChooseAnimation::F_Player_Select_May);
				FirstPlayerCurrentPos = EITT_SelectCharacter::May;
			}
			else if(NextPosition == EITT_SelectCharacter::Cody)
			{
				PlayAnimationByName(ChooseAnimation::F_Player_Select_Cody);
				FirstPlayerCurrentPos = EITT_SelectCharacter::Cody;
			}
			return;
		}
		
		if(FirstPlayerCurrentPos == EITT_SelectCharacter::Cody && NextPosition == EITT_SelectCharacter::None)
		{
			PlayAnimationByName(ChooseAnimation::F_Player_UnSelect_Cody);
			FirstPlayerCurrentPos = EITT_SelectCharacter::None;
		}
	}
	else if(Player == ITT_Player::Second)
	{
		if(SecondPlayerCurrentPos == EITT_SelectCharacter::May && NextPosition == EITT_SelectCharacter::None)
		{
			PlayAnimationByName(ChooseAnimation::S_Player_UnSelect_May);
			FirstPlayerCurrentPos = EITT_SelectCharacter::None;
			return;
		}
		
		if(SecondPlayerCurrentPos == EITT_SelectCharacter::None)
		{
			if(NextPosition == EITT_SelectCharacter::May)
			{
				PlayAnimationByName(ChooseAnimation::S_Player_Select_May);
				FirstPlayerCurrentPos = EITT_SelectCharacter::May;
			}
			else if(NextPosition == EITT_SelectCharacter::Cody)
			{
				PlayAnimationByName(ChooseAnimation::S_Player_Select_Cody);
				FirstPlayerCurrentPos = EITT_SelectCharacter::Cody;
			}
			return;
		}
		
		if(SecondPlayerCurrentPos == EITT_SelectCharacter::Cody && NextPosition == EITT_SelectCharacter::None)
		{
			PlayAnimationByName(ChooseAnimation::S_Player_UnSelect_Cody);
			FirstPlayerCurrentPos = EITT_SelectCharacter::None;
		}
	}
}

void UITT_Widget_Choose_Character::SelectCharacterState(ECommonInputType CommonInput) const
{
	CPP_1P->SetJoyStick(static_cast<int32>(CommonInput));
}
