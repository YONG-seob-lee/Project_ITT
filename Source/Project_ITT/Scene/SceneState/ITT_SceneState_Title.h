// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Scene/ITT_SceneBase.h"
#include "ITT_SceneState_Title.generated.h"

namespace SocketName
{
	const FName MayAttach = TEXT("MayAttach_Socket");
	const FName CodyAttach = TEXT("CodyAttach_Socket");
}
/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SceneState_Title : public UITT_SceneBase
{
	GENERATED_BODY()
	
protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
	virtual bool LoadingPostProcess(float DeltaTime) override;

private:
	void CreatePlayer();
	void ResetPlayer();
	void ChangeCamera() const;
	void CreateDoll() const;
	
	TWeakObjectPtr<class UITT_BasePlayer_Rose> Player;
	TArray<TWeakObjectPtr<class UITT_BasePlayer>> Dolls;
	TWeakObjectPtr<class AITT_PlayerSpawnPoint> PlayerSpawnPoint = nullptr;

	bool bFirst = false;
};
