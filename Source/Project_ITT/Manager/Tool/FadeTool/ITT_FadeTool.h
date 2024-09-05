// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_FadeCommand.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "UObject/Object.h"
#include "ITT_FadeTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_FadeTool : public UObject
{
	GENERATED_BODY()
public:
	void Initialize();
	
	void Request(class UITT_FadeCommand* Command);
	void FinishRequest();

	void Tick(float DeltaTime);
	
private:
	void StartFadeOut();
	void StartFadeIn();

	void PlayFadeAnimation(EITT_FadeStyle FadeType, bool bFadeOut, bool bDirectFadeIn);
	void OnWidgetFadeOutFinished();
	void OnWidgetFadeInFinished();

	EITT_FadeStep CurrentStep = EITT_FadeStep::Ready;
	bool bLoadStart = false;
	bool bLoadComplete = false;

	float LoadingMinimumTime = 0.f;
	float LoadElapsedTime = 0.f;

	UPROPERTY()
	TArray<TObjectPtr<UITT_FadeCommand>> Commands;
	UPROPERTY()
	TObjectPtr<UITT_FadeCommand> FadeWidgetCommand = nullptr;
	UPROPERTY()
	TObjectPtr<class UITT_Widget_DialogScreenFader> DialogScreenFader = nullptr;

#define CREATE_FADE_COMMAND(CommandName) \
TObjectPtr<class UITT_FadeCommand> CommandName = ITT_NewObject<UITT_FadeCommand>(); \
CommandName->AddToRoot(); \
CommandName->SetCreateFrom(__FILE__, __LINE__);
};
