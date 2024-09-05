// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ITT_TitleDefine.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"
#include "ITT_State_SelectPickMove.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_State_SelectPickMove : public UITT_StateBase
{
	GENERATED_BODY()
	/**
 *   Title 씬에서 캐릭터 선택 및 조이스틱 선택 좌우 움직임을 위한 스테이트 클래스
 */
public:	
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

private:
	void OnAxisSelect(float AxisValue);

	// 플레이어들의 상황을 저장하는 데이터
	FITT_SelectData SelectData;
	
	TWeakObjectPtr<class UITT_BasePlayer_Rose> RoseUnit = nullptr; 
	TWeakObjectPtr<class AITT_CharacterBase> RoseCharacter = nullptr;
	TWeakObjectPtr<class UITT_AnimInstance_Rose> RoseAnimInst = nullptr;
	TWeakObjectPtr<class UITT_AnimInstance_Doll> CodyAnimInst = nullptr;
	TWeakObjectPtr<class UITT_AnimInstance_Doll> MayAnimInst = nullptr;
	TWeakObjectPtr<class UITT_Widget_Title> TitleWidget = nullptr;
	
	FVector2d JoyStickDistance = FVector2d::ZeroVector;

	bool bFinishedInitialize = false;
};
