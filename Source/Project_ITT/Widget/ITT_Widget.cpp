// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Widget.h"

#include "MovieScene.h"
#include "Animation/WidgetAnimation.h"

void UITT_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UITT_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UITT_Widget::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	bManaged = _bManaged;

	FillDefaultAnimations();
	
	if(bActivate)
	{
		Active(true);
	}

	InitResourceWidgetInfo();
}

void UITT_Widget::FinishWidget()
{
	if(IsValid(this) == false || this->IsValidLowLevel() == false)
	{
		return;
	}
	
	StopAllAnimations();
	Active(false);
}

void UITT_Widget::Active(bool _bActive /* = true */)
{
	if(bAddToViewport == false)
	{
		AddToViewport(_bActive ? ZOrder : 0);
	}
	
	if(IsVisible())
	{
		if(IsExistAnim(DefaultWidgetAnimation::Appearance) == true)
		{
			PlayAnimationByName(DefaultWidgetAnimation::Appearance);
		}

		if(_bActive == false)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	bActive = _bActive;
}

void UITT_Widget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UITT_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UITT_Widget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationStarted_Implementation(Animation);
}

void UITT_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	OnAnimFinished(FName(Animation->GetMovieScene()->GetName()));
}

void UITT_Widget::Init()
{
	bActive = false;
	bAddToViewport = false;
}

void UITT_Widget::PlayAnimationByName(FName Name, float StartTime, int32 LoopCount, EUMGSequencePlayMode::Type PlayType, float Speed)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(Name))
	{
		PlayAnimation(WidgetAnimation, StartTime, LoopCount, PlayType, Speed);
	}
}

TObjectPtr<UWidgetAnimation> UITT_Widget::GetAnimationByName(FName AnimName) const
{
	TObjectPtr<UWidgetAnimation> const* pWidgetAnim = Animations.Find(AnimName);

	return pWidgetAnim == nullptr ? nullptr : *pWidgetAnim;
}

bool UITT_Widget::StopAnimation(const FName& AnimName)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(AnimName))
	{
		UUserWidget::StopAnimation(WidgetAnimation);
		return true;
	}

	return false;
}

bool UITT_Widget::IsExistAnim(FName AnimName) const
{
	const TObjectPtr<UWidgetAnimation> WidgetAnim = GetAnimationByName(AnimName);

	return WidgetAnim != nullptr;
}

void UITT_Widget::InitResourceWidgetInfo()
{
	if(bManaged == false)
	{
		return;
	}
}

void UITT_Widget::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		if(GetAnimationByName(DefaultWidgetAnimation::Idle))
		{
			PlayAnimationByName(DefaultWidgetAnimation::Idle, 0.f, 0);
		}
	}
}

void UITT_Widget::FillDefaultAnimations()
{
	Animations.Empty();

	FProperty* Property = GetClass()->PropertyLink;
	while(Property != nullptr)
	{
		if(Property->GetClass() == FObjectProperty::StaticClass())
		{
			if(const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
			{
				if(ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					TObjectPtr<UWidgetAnimation> WidgetAnimObject = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this));

					if(WidgetAnimObject && WidgetAnimObject->MovieScene != nullptr)
					{
						Animations.Emplace(WidgetAnimObject->GetMovieScene()->GetName(), WidgetAnimObject);
					}
				}
			}
		}
		Property = Property->PropertyLinkNext;
	}
}
