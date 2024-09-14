// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ITT_TitleDefine.h"
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
	void CreateDummyPlayer();
	void ResetPlayer();
	void ChangeCamera() const;
	void CreateDoll() const;

	void OnAxisSelect(ITT_Player PlayerIndex, float AxisValue);
	void OnPickDoll();
	
	TWeakObjectPtr<class AITT_PlayerSpawnPoint> PlayerSpawnPoint = nullptr;
	TWeakObjectPtr<class AITT_PlayerSpawnPoint> DummySpawnPoint = nullptr;
	
	TWeakObjectPtr<class UITT_BasePlayer_Rose> Player;
	TWeakObjectPtr<class UITT_BasePlayer_Dummy> Dummy;
	
	TArray<TWeakObjectPtr<class UITT_BasePlayer>> Dolls;
	TWeakObjectPtr<class UITT_AnimInstance_Rose> RoseAnimInst = nullptr;
	
	// 플레이어들의 상황을 저장하는 데이터
	FITT_SelectData SelectData;
	TWeakObjectPtr<class UITT_Widget_Title> TitleWidget = nullptr;

	bool bFirst = false;
};
