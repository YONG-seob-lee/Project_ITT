// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget_Select.h"

#include "Components/ScrollBox.h"
#include "Framework/Application/NavigationConfig.h"
#include "Manager/ITT_InputManager.h"
#include "PROJECT_ITT/Manager/ITT_SceneManager.h"
#include "PROJECT_ITT/Manager/ITT_TableManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Manager/Tool/FadeTool/ITT_FadeTool.h"
#include "PROJECT_ITT/Table/Mapper/ITT_Mapper_SelectButton.h"
#include "PROJECT_ITT/Widget/Button/ITT_SelectButton.h"

void UITT_Widget_Select::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	UITT_Mapper_SelectButton* SelectMapper = Cast<UITT_Mapper_SelectButton>(gTableMng.GetTableMapper(EITT_TableDataType::SelectButton));
	TMap<int32, FSelectButton*>* ButtonDatas = SelectMapper->GetSelectButtonDatas();
	if(ButtonDatas == nullptr)
	{
		return;
	}
	
	InitScrollBox(ButtonDatas);
}

void UITT_Widget_Select::NativeConstruct()
{
	Super::NativeConstruct();
	gInputMng.GetMoveButtonDelegate().AddUObject(this, &UITT_Widget_Select::OnMoveButtonEvent);
	
	TMap<FKey, EUINavigation>& KeyEventRules = FSlateApplication::Get().GetNavigationConfig()->KeyEventRules;
	KeyEventRules.Emplace(EKeys::F, EUINavigation::Up);
	KeyEventRules.Emplace(EKeys::V, EUINavigation::Down);
	
	CPP_SelectScrollBox->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Wrap);
	CPP_SelectScrollBox->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Wrap);
	

	for(const auto& Button : CPP_SelectScrollBox->GetAllChildren())
	{
		TArray<TObjectPtr<UITT_Button>> InButtons;
		if(TObjectPtr<UITT_Widget> ButtonWidget = Cast<UITT_Widget>(Button))
		{
			ButtonWidget->GetButtons(InButtons);
		}

		for(const auto& InButton :InButtons)
		{
			Buttons.Emplace(InButton);
		}
	}
}

void UITT_Widget_Select::NativeDestruct()
{
	gInputMng.GetMoveButtonDelegate().RemoveAll(this);
	Super::NativeDestruct();
}

void UITT_Widget_Select::InitScrollBox(TMap<int32, FSelectButton*>* ButtonDatas) const
{
	if(CPP_SelectScrollBox)
	{
		CPP_SelectScrollBox->ClearChildren();
		
		for(const auto& ButtonData : *ButtonDatas)
		{
			UITT_Widget_SelectButton* Button = Cast<UITT_Widget_SelectButton>(gWidgetMng.Create_Widget_NotManaging(UITT_Widget_SelectButton::GetWidgetPath()));

			if(Button == nullptr)
			{
				ITT_LOG(TEXT("Widget Is not Exist. Please Cheak Referance Path."));
				return;
			}

			CPP_SelectScrollBox->AddChild(Button);
			Button->SetButtonData(ButtonData.Value->ButtonName);
			Button->SetOnClickSelectButtonFunc([ButtonData, this]()
			{
				if(ButtonData.Value->SceneType == static_cast<int32>(EITT_GameSceneType::Title))
				{
					if(OnChangeStoryCallback)
					{
						OnChangeStoryCallback();
						return;
					}
				}
				
				CREATE_FADE_COMMAND(Command);
				Command->SetFadeStyle(EITT_FadeStyle::Dialog);
				Command->SetIsDirectFadeOut(false);
				Command->SetLoadingPageType(EITT_LoadingPageType::None);
				Command->OnCheckLoadComplete = FITT_FadeCheckLoadDelegate::CreateWeakLambda(this, []()
				{
					return gSceneMng.IsCompleteChangeScene();
				});
				gSceneMng.ChangeScene(static_cast<EITT_GameSceneType>(ButtonData.Value->SceneType), Command);
			});
			Button->PlayAppearance();
		}
	}
}

void UITT_Widget_Select::OnMoveButtonEvent(bool bMoveUp)
{
	for(const auto& Button : Buttons)
	{
		if(Button.Get()->IsHovered())
		{
			SelectButtonIndex = Buttons.IndexOfByKey(Button.Get());
		}
	}

	if(bMoveUp)
	{
		if(SelectButtonIndex > 0)
		{
			SelectButtonIndex -= 1;
		}
	}
	else
	{
		SelectButtonIndex += 1;
	}
	
	for(int32 i = 0 ; i < Buttons.Num() ; i++)
	{
		if(i == SelectButtonIndex)
		{
			Buttons[i].Get()->OnHoverJoyStick();	
		}
		else
		{
			Buttons[i].Get()->UnHoverJoyStick();	
		}
	}
}

void UITT_Widget_SelectButton::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
	
	UCommonButtonBase::FCommonButtonEvent ButtonEvent;
	ButtonEvent.AddUObject(this, &UITT_Widget_SelectButton::OnClickButton);
	CPP_SelectButton->SetOnClickedDelegate(ButtonEvent);

	MakeButtonPool();
}

void UITT_Widget_SelectButton::SetButtonData(const FString& ButtonName) const
{
	if(CPP_SelectButton)
	{
		CPP_SelectButton->SetButtonData(ButtonName);
	}
}

void UITT_Widget_SelectButton::PlayAppearance()
{
	PlayAnimationByName(DefaultWidgetAnimation::Appearance);
}

void UITT_Widget_SelectButton::OnClickButton()
{
	if(OnClickSelectButtonCallback)
	{
		OnClickSelectButtonCallback();
	}

	gWidgetMng.DestroyWidget(UITT_Widget_Select::GetWidgetName());
}
