// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_State_SelectPickMove.h"

#include "Animation/ITT_AnimInstance_Doll.h"
#include "Animation/ITT_AnimInstance_Rose.h"
#include "PROJECT_ITT/Manager/ITT_InputManager.h"
#include "PROJECT_ITT/Manager/ITT_WidgetManager.h"
#include "PROJECT_ITT/Widget/Title/ITT_Widget_Title.h"
#include "Unit/ITT_BasePlayer_Rose.h"

void UITT_State_SelectPickMove::Begin()
{
	SelectData = FITT_SelectData();
	
	gInputMng.TestDelegate.AddUObject(this, &UITT_State_SelectPickMove::OnAxisSelect);
	
	// 캐릭터 선택때 필요한 좌,우 축 바인딩을 위함
	FInputAxisUnifiedDelegate SelectDelegate;
	SelectDelegate.BindDelegate(this, &UITT_State_SelectPickMove::OnAxisSelect);
	gInputMng.RegistAxis(EITT_Axis_Type::Left, EITT_Action_Type::ActionLeftRight, SelectDelegate);

	TitleWidget = Cast<UITT_Widget_Title>(gWidgetMng.GetWidget(UITT_Widget_Title::GetWidgetName()));

	if(TitleWidget.IsValid() == false)
	{
		ITT_LOG(TEXT("Title widget is not valid! Please check Widget Instance or Table"));
	}

	RoseUnit = Cast<UITT_BasePlayer_Rose>(GetOuter());
	if(RoseUnit.IsValid() == false)
	{
		return;
	}
	RoseCharacter = RoseUnit.Get()->GetCharacterBase();
	if(RoseCharacter.IsValid() == false)
	{
		return;
	}
	
	RoseAnimInst = Cast<UITT_AnimInstance_Rose>(RoseCharacter->GetAnimInstance());
	if(RoseAnimInst.IsValid() == false)
	{
		return;
	}
}

void UITT_State_SelectPickMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bFinishedInitialize)
	{
		return;
	}

	TitleWidget = Cast<UITT_Widget_Title>(gWidgetMng.GetWidget(UITT_Widget_Title::GetWidgetName()));
	MayAnimInst = RoseUnit->GetDollAnimInstance(0);
	CodyAnimInst = RoseUnit->GetDollAnimInstance(1);

	if(TitleWidget.IsValid() && MayAnimInst.IsValid() && CodyAnimInst.IsValid())
	{
		bFinishedInitialize = true;
	}
}

void UITT_State_SelectPickMove::Exit()
{
	gInputMng.TestDelegate.RemoveAll(this);
	Super::Exit();
}

void UITT_State_SelectPickMove::OnAxisSelect(float AxisValue)
{
	if(bFinishedInitialize == false)
	{
		return;	
	}
	
	if(FMath::IsNearlyEqual(AxisValue, 0.f))
	{
		return;
	}
	
	const bool bMoveRight = AxisValue > 0;
	const FITT_ResultSelectData ResultData = SelectData.SetPlayerData(ITT_Player::First, bMoveRight);
	if(ResultData.bChanged)
	{
		TitleWidget->RefreshCharacterState(ResultData.Player, ResultData.NextPosition);
	}

	if(RoseAnimInst.IsValid())
	{
		RoseAnimInst->Select(AxisValue);
	}

	if(MayAnimInst.IsValid() && CodyAnimInst.IsValid())
	{
		if(AxisValue > 0)
		{
			MayAnimInst->Select(0.f);
			CodyAnimInst->Select(1.f);
		}
		else if(AxisValue < 0)
		{
			MayAnimInst->Select(1.f);
			CodyAnimInst->Select(0.f);
		}
		else
		{
			MayAnimInst->Select(0.f);
			CodyAnimInst->Select(0.f);
		}
	}
}
