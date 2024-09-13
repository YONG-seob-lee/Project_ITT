// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "../ITT_Define.h"
#include "ITT_SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SceneManager : public UObject, public UITT_Singleton<UITT_SceneManager>
{
	GENERATED_BODY()

public:
	UITT_SceneManager();
	~UITT_SceneManager();
	
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<class UITT_SceneBase> GetCurrentScene() const;
	FORCEINLINE EITT_GameSceneType GetCurrentSceneType() { return CurrentSceneType; }
	
	FORCEINLINE bool IsCompleteChangeScene() const { return ChangeSceneData.Step == EITT_ChangeSceneStep::Complete; }
	
	bool LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr, const FITT_LoadLevelInitialized& Delegate);
	void ExecuteLoadLevelDelegate(const FString& LevelName = TEXT(""));

	void RegisterSceneStates();
	void ChangeScene(EITT_GameSceneType SceneType, TObjectPtr<class UITT_FadeCommand> Command = nullptr);
	void SceneLoadComplete(float LoadTime, const FString& LevelName);

	bool LoadLevelByPath(const FITT_LoadLevelInitialized& Delegate, const FName& PackagePath = FName(), bool bAbsolute = true);

	
	FITT_ChangeSceneDelegate OnChangeScene;
	
	FITT_LoadLevelInitialized LoadLevelInitialized;
	
	FITT_LoadLevelDelegate OnStartLevelLoading;
	FITT_LoadLevelDelegate OnFinishedLevelLoading;
	
	FITT_ChangeSceneState OnCompleteChangeScene;
private:
	void RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UITT_StateBase> SceneType) const;

	bool ChangeSceneStep_Fade(const TObjectPtr<UITT_FadeCommand>& Command);
	bool ChangeSceneStep_LoadLevel();
	void ChangeSceneStep_SetSceneState(uint8 SceneId);
	
	void OnCompleteLevelLoading(const FString& LevelPackagePath);
	
	UPROPERTY()
	FITT_ChangeSceneData ChangeSceneData;
	
	UPROPERTY()
	TObjectPtr<class UITT_StateMachine> SceneStateMachine = nullptr;
	
	UPROPERTY()
	TMap<FString, bool> ActiveLevels;

	UPROPERTY()
	TMap<EITT_GameSceneType, FString> ScenePath;
	
	UPROPERTY()
	TObjectPtr<class UITT_FadeTool> FadeTool = nullptr;

	EITT_GameSceneType CurrentSceneType;
#define	gSceneMng (*UITT_SceneManager::GetInstance())
};
