// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_VirtualJoyStick.h"

#include "PROJECT_ITT/Manager/ITT_UnitManager.h"
#include "PROJECT_ITT/Table/Resource_Unit.h"
#include "PROJECT_ITT/Unit/ITT_UnitBase.h"

int32 SITT_VirtualJoyStick::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                    const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 RetLayerId = LayerId;

	if(bVisible == false)
	{
		return SVirtualJoystick::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}
	
	const FLinearColor ColorAndOpacity = InWidgetStyle.GetColorAndOpacityTint();
	FLinearColor CenterImageColor = ColorAndOpacity;
	CenterImageColor.A = CenterImageOpacity;

	if(ImageCenter.IsValid())
	{
		FSlateDrawElement::MakeBox(OutDrawElements, RetLayerId++, AllottedGeometry.ToPaintGeometry(VisualCenter - FVector2d(CorrectedCenterImageSize.X * 0.5f, CorrectedCenterImageSize.Y * 0.5f), CorrectedCenterImageSize),
									ImageCenter->GetSlateBrush(), ESlateDrawEffect::None, CenterImageColor);
	}

	if(CapturePointerIndex != -1)
	{
		FLinearColor OuterImageColor = ColorAndOpacity;
		OuterImageColor.A = OuterImageOpacity;

		const FVector DefaultRotateVector = FVector(0.f, -1.f, 0.f);
		FVector CurrentRotateVector = FVector(ThumbPosition.X, ThumbPosition.Y, 0.f);
		CurrentRotateVector.Normalize();

		const FRotator DefaultRotator = DefaultRotateVector.ToOrientationRotator();
		const FRotator CurrentRotator = CurrentRotateVector.ToOrientationRotator();

		const float RotationDegree = CurrentRotator.Yaw - DefaultRotator.Yaw;
		const float RotationRadian = FMath::DegreesToRadians(RotationDegree);

		float OuterImageScale = 0.5f;

		if(const TObjectPtr<UITT_UnitBase> SelfPlayer = gUnitMng.GetUnit(gUnitMng.GetIsValidBasePlayer()))
		{
			const float MovingSpeed = SelfPlayer->GetMovingSpeed();
			if(MovingSpeed >= SelfPlayer->GetResourceUnitData()->RunSpeed)
			{
				OuterImageScale = 1.f;
			}
			else
			{
				OuterImageScale = 0.5f;
			}
		}

		if(ImageOuter.IsValid())
		{
			FSlateDrawElement::MakeRotatedBox(
					OutDrawElements,
					RetLayerId++,
					AllottedGeometry.ToPaintGeometry(VisualCenter - FVector2D(CorrectedOuterImageSize.X * 0.5f , CorrectedOuterImageSize.Y * 0.5f) * OuterImageScale,
						CorrectedOuterImageSize * OuterImageScale),	ImageOuter->GetSlateBrush(), ESlateDrawEffect::None, RotationRadian, TOptional<FVector2D>(),
						FSlateDrawElement::ERotationSpace::RelativeToElement, OuterImageColor
				);
		}

		RetLayerId = SVirtualJoystick::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}
	return RetLayerId;
}

FReply SITT_VirtualJoyStick::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	return SVirtualJoystick::OnTouchStarted(MyGeometry, InTouchEvent);
}

FReply SITT_VirtualJoyStick::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	return SVirtualJoystick::OnTouchMoved(MyGeometry, InTouchEvent);
}

FReply SITT_VirtualJoyStick::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	return SVirtualJoystick::OnTouchEnded(MyGeometry, InTouchEvent);
}

void SITT_VirtualJoyStick::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SVirtualJoystick::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

bool SITT_VirtualJoyStick::HandleTouch(int32 ControlIndex, const FVector2D& LocalCoordinate,
	const FVector2D& ScreenSize)
{
	return SVirtualJoystick::HandleTouch(ControlIndex, LocalCoordinate, ScreenSize);
}

void SITT_VirtualJoyStick::HandleDisplayMetricsChanged(const FDisplayMetrics& NewDisplayMetric)
{
	SVirtualJoystick::HandleDisplayMetricsChanged(NewDisplayMetric);
}

bool SITT_VirtualJoyStick::IsActiveJoyStick()
{
	return true;
}
