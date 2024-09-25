// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Scene/ITT_SceneBase.h"
#include "ITT_SceneState_Practice.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SceneState_Practice : public UITT_SceneBase
{
	GENERATED_BODY()
	
protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
	virtual bool LoadingPostProcess(float DeltaTime) override;

private:
	void CreatePlayer(const TWeakObjectPtr<class AITT_PlayerSpawnPoint>& _PlayerSpawnPoint);
	void ResetPlayer();
	void ChangeCamera();
	
	TArray<TWeakObjectPtr<class UITT_BasePlayer>> Players;
	TArray<TWeakObjectPtr<class AITT_PlayerSpawnPoint>> PlayerSpawnPoints;
};
