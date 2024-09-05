// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_PreTouchProcessor.h"

#include "PROJECT_ITT/ITT_Define.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Widget/Button/ITT_Widget_Touch.h"
#include "Slate/SceneViewport.h"

void FITT_PreTouchProcessor::Initialize()
{
	ChangeTouchEffect(EffectThings::DefaultEffectId);
}

void FITT_PreTouchProcessor::Finalize()
{
	ClearTouchEffect();
}

void FITT_PreTouchProcessor::AddReferencedObjects(FReferenceCollector& Collector)
{
	if(TouchOverlapEffect.Num() > 0)
	{
		Collector.AddReferencedObjects(TouchOverlapEffect);
	}
}

FString FITT_PreTouchProcessor::GetReferencerName() const
{
	return TEXT("FCY_PreTouchProcessor");
}

void FITT_PreTouchProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
	while(TouchEffectQueue.IsEmpty() == false)
	{
		TouchEffectQueue.Pop();		
	}
}

bool FITT_PreTouchProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FingerCount++;
	
	FingerTouchIndex = MouseEvent.GetPointerIndex();
	ITT_LOG(TEXT("FingerTouchIndex = %d"), FingerTouchIndex);	
	
	Touch(MouseEvent.GetScreenSpacePosition());
	return false;
}

bool FITT_PreTouchProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if(FingerCount == 2)
	{
		// MiniMap Zoomin Process
	}
	
	return IInputProcessor::HandleMouseMoveEvent(SlateApp, MouseEvent);
}

bool FITT_PreTouchProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FingerCount--;
	
	TouchOverlapEffect[TouchEffectIndex]->RemoveFromParent();
	TouchOverlapEffect.Remove(TouchEffectIndex);
	TouchOverlapEffect.Emplace(TouchEffectIndex, Cast<UITT_Widget_Touch>(gWidgetMng.Create_Widget_NotManaging(EffectThings::DefaultTouchEffectPath)));
	
	const int32 PointerIndex = MouseEvent.GetPointerIndex();
	if(FingerTouchIndex != -1 && FingerTouchIndex != MouseEvent.GetPointerIndex())
	{
		SlateApp.RoutePointerUpEvent(FWidgetPath(), FPointerEvent(MouseEvent.GetUserIndex(), PointerIndex,
			FVector2d(-10000.f, -10000.f), FVector2d(-10000.f, -10000), false, false));
		return true;
	}

	TouchEffectQueue.Enqueue(PointerIndex);
	FingerTouchIndex = -1;
	
	return false;
}

void FITT_PreTouchProcessor::UpdateTouchWidget()
{
	for(const auto& TouchEffect : TouchOverlapEffect)
	{
		if(IsValid(TouchEffect.Value))
		{
			TouchEffect.Value->RebuildTouchWidget();
		}
	}
}

void FITT_PreTouchProcessor::CreateTouchEffect()
{
	if(TouchOverlapEffect.Num() > 0)
	{
		ClearTouchEffect();
	}

	for(int32 i = 0 ; i < EffectThings::EffectOverlapMaxCount ; i++)
	{
		TObjectPtr<UITT_Widget_Touch> EffectWidget = Cast<UITT_Widget_Touch>(gWidgetMng.Create_Widget_NotManaging(EffectThings::DefaultTouchEffectPath));
		if(IsValid(EffectWidget))
		{
			EffectWidget->InitWidget(FName(EffectThings::DefaultTouchEffectPath), false, false);
			EffectWidget->AddToViewport(99999);
			EffectWidget->Active(true);
			TouchOverlapEffect.Emplace(i, EffectWidget);
		}
	}
}

void FITT_PreTouchProcessor::ChangeTouchEffect(int32 TouchEffectId)
{
	if(TouchEffectId == EffectThings::DefaultEffectId)
	{
		CreateTouchEffect();
		CurrentTouchEffectId = TouchEffectId;
		return;
	}
}

void FITT_PreTouchProcessor::ClearTouchEffect()
{
	for(const auto& TouchEffect : TouchOverlapEffect)
	{
		if(IsValid(TouchEffect.Value))
		{
			TouchEffect.Value->SetVisibility(ESlateVisibility::Collapsed);
			TouchEffect.Value->StopAnimation(EffectThings::Anim);
		}
	}

	TouchOverlapEffect.Empty();
}

void FITT_PreTouchProcessor::Touch(const FVector2d& ScreenPosition)
{
	if(TouchOverlapEffect.Contains(TouchEffectIndex) == false)
	{
		return;
	}

	const FGeometry CachedGeometry = UITT_InstUtil::GetGameViewport()->GetCachedGeometry();
	const FVector2d AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(ScreenPosition);

	TouchOverlapEffect[TouchEffectIndex]->AddToViewport(99999);
	TouchOverlapEffect[TouchEffectIndex]->SetPositionInViewport(AbsoluteScreenPosition);
	TouchOverlapEffect[TouchEffectIndex]->PlayTouch();
	TouchEffectIndex = (TouchEffectIndex + 1) % EffectThings::EffectOverlapMaxCount;


// #if WITH_EDITOR
// 	UITT_InstUtil::ShowMessageOnScreen(TEXT("FCY_PreTouchProcessor::Touch"));
// #endif
}
