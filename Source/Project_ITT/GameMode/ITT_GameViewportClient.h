// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "ITT_GameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_GameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
public:
	virtual void Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice) override;
	
	virtual void UpdateActiveSplitscreenType() override;
	void UpdateActiveSplitScreenType(ESplitScreenType::Type _ScreenType);
	virtual void LayoutPlayers() override;

	void SetSplitScreenInfo(FVector2D MoveVector);

private:
	void RefreshRatio();

	FVector2D SizeRatio = FVector2D(0.5f, 0.5f);
};
