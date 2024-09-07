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
};
