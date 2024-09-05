// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneManager.h"

#include "ITT_InputManager.h"
#include "ITT_WidgetManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Scene/ITT_SceneBase.h"
#include "PROJECT_ITT/Scene/SceneState/ITT_SceneState_Chapter01.h"
#include "PROJECT_ITT/Scene/SceneState/ITT_SceneState_Chapter02.h"
#include "PROJECT_ITT/Scene/SceneState/ITT_SceneState_Logo.h"
#include "PROJECT_ITT/Scene/SceneState/ITT_SceneState_Practice.h"
#include "PROJECT_ITT/Scene/SceneState/ITT_SceneState_Title.h"
#include "PROJECT_ITT/StateMachine/ITT_StateMachine.h"
#include "Tool/FadeTool/ITT_FadeCommand.h"
#include "Tool/FadeTool/ITT_FadeTool.h"

UITT_SceneManager::UITT_SceneManager()
{
}

UITT_SceneManager::~UITT_SceneManager()
{
}

void UITT_SceneManager::BuiltInInitialize()
{
	if(SceneStateMachine)
	{
		return;
	}
	
	SceneStateMachine = ITT_NewObject<UITT_StateMachine>(this, UITT_StateMachine::StaticClass());
	SceneStateMachine->AddToRoot();
	SceneStateMachine->Create();
}

void UITT_SceneManager::Initialize()
{
	FadeTool = ITT_NewObject<UITT_FadeTool>();
	if(IsValid(FadeTool))
	{
		FadeTool->Initialize();
	}
	
	ScenePath.Emplace(EITT_GameSceneType::Logo, LevelPath::Logo);
	ScenePath.Emplace(EITT_GameSceneType::Title, LevelPath::Title);
	ScenePath.Emplace(EITT_GameSceneType::Chapter_01, LevelPath::Chapter_1);
	ScenePath.Emplace(EITT_GameSceneType::Chapter_02, LevelPath::Chapter_2);
	ScenePath.Emplace(EITT_GameSceneType::Practice, LevelPath::Practice);
}

void UITT_SceneManager::PostInitialize()
{
}

void UITT_SceneManager::Finalize()
{
	 ITT_DeleteObject(FadeTool);
	 FadeTool = nullptr;
	
	 LoadLevelInitialized.Unbind();
	 LoadLevelInitialized = nullptr;
}

void UITT_SceneManager::BuiltInFinalize()
{
	SceneStateMachine->Destroy();
	SceneStateMachine->RemoveFromRoot();
	SceneStateMachine = nullptr;
}

void UITT_SceneManager::Tick(float DeltaTime)
{
	if(IsValid(FadeTool))
	{
		FadeTool->Tick(DeltaTime);
	}

	
	if(ChangeSceneData.Step == EITT_ChangeSceneStep::Complete)
	{
		if(SceneStateMachine)
		{
			SceneStateMachine->Tick(DeltaTime);
		}
	}
	else if(ChangeSceneData.Step == EITT_ChangeSceneStep::PrepareSceneState)
	{
		const TObjectPtr<UITT_SceneBase> CurrentScene = GetCurrentScene();
		if(IsValid(CurrentScene) == false)
		{
			return;
		}

		CurrentScene->TickLoading(DeltaTime);
		if(CurrentScene->IsCompleteLoading())
		{
			ChangeSceneData.Step = EITT_ChangeSceneStep::Complete;
		}
	}
}

TObjectPtr<UITT_SceneBase> UITT_SceneManager::GetCurrentScene() const
{
	if(SceneStateMachine)
	{
		return Cast<UITT_SceneBase>(SceneStateMachine->GetCurrentState());
	}

	return nullptr;
}

bool UITT_SceneManager::LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr, const FITT_LoadLevelInitialized& Delegate)
{
	const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
	if(IsValid(World) == false)
	{
		return false;
	}

	//gInputMng.DestroyInputPawn();
	//gCameraMng.DestroyAllCameras();

	bool bSuccess = true;
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(World, LevelObjectPtr, FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

	if(bSuccess)
	{
		if(LoadLevelInitialized.IsBound())
		{
			LoadLevelInitialized.Unbind();
		}
		
		LoadLevelInitialized = Delegate;
	}

	return true;
}

void UITT_SceneManager::ExecuteLoadLevelDelegate(const FString& LevelName)
{
	if(LoadLevelInitialized.IsBound())
	{
		const FITT_LoadLevelInitialized Delegate = LoadLevelInitialized;
		LoadLevelInitialized.Unbind();
		
		Delegate.Execute(LevelName.IsEmpty() ? UITT_InstUtil::GetGameWorld()->GetMapName() : LevelName);
	}
}

void UITT_SceneManager::RegisterSceneStates()
{
	RegistSceneState(static_cast<uint8>(EITT_GameSceneType::Logo), TEXT("Logo"), UITT_SceneState_Logo::StaticClass());
	RegistSceneState(static_cast<uint8>(EITT_GameSceneType::Title), TEXT("Title"), UITT_SceneState_Title::StaticClass());
	RegistSceneState(static_cast<uint8>(EITT_GameSceneType::Chapter_01), TEXT("Chapter_01"), UITT_SceneState_Chapter01::StaticClass());
	RegistSceneState(static_cast<uint8>(EITT_GameSceneType::Chapter_02), TEXT("Chapter_02"), UITT_SceneState_Chapter02::StaticClass());
	RegistSceneState(static_cast<uint8>(EITT_GameSceneType::Practice), TEXT("Practice"), UITT_SceneState_Practice::StaticClass());
}

void UITT_SceneManager::ChangeScene(EITT_GameSceneType SceneType, TObjectPtr<UITT_FadeCommand> Command /* = nullptr */)
{
	if(OnChangeScene.IsBound())
	{
		OnChangeScene.Broadcast(SceneType);
	}

	const FString* LevelPath = ScenePath.Find(SceneType);
	
	const FString LevelPackagePath = LevelPath ? *LevelPath : FString();
	
	ITT_LOG(TEXT("UITT_SceneManager::ChangeScene - SceneId(%d), LevelPath(%s)"), SceneType, *LevelPackagePath);
	
	ChangeSceneData.Step = EITT_ChangeSceneStep::Ready;
	ChangeSceneData.SceneType = SceneType;
	ChangeSceneData.LevelPackagePath = FName(LevelPackagePath);

	if(Command)
	{
		ChangeSceneStep_Fade(Command);
	}
	else
	{
		ChangeSceneStep_LoadLevel();
	}
	
	gWidgetMng.ClearExclusiveLayer();
}

void UITT_SceneManager::SceneLoadComplete(float LoadTime, const FString& LevelName)
{
	gInputMng.CreateInputPawn();
	ActiveLevels.Empty();

	const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
	const TArray<ULevelStreaming*>& Levels = World->GetStreamingLevels();

	for(int32 i = 0 ; i < Levels.Num() ; i++)
	{
		if(World->GetCurrentLevel()->GetName().Equals(Levels[i]->PackageNameToLoad.ToString(), ESearchCase::IgnoreCase))
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), true);
		}
		else
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), false);
		}
	}

	ExecuteLoadLevelDelegate(LevelName);
}

bool UITT_SceneManager::LoadLevelByPath(const FITT_LoadLevelInitialized& Delegate, const FName& PackagePath, bool bAbsolute)
{
	if(UITT_InstUtil::HasGameInstance() == false)
	{
		return false;
	}

	const TObjectPtr<UWorld> World = UITT_InstUtil::GetGameWorld();
	if(World == nullptr)
	{
		return false;
	}

	//gInputMng.DestroyInputPawn();
	//gCameraMng.DestroyAllCameras();

	UGameplayStatics::OpenLevel(World, PackagePath, bAbsolute);

	LoadLevelInitialized.Unbind();
	LoadLevelInitialized = Delegate;

	return true;
}

void UITT_SceneManager::RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<UITT_StateBase> SceneType) const
{
	SceneStateMachine->RegistState(SceneId, Name, SceneType);
}

bool UITT_SceneManager::ChangeSceneStep_Fade(const TObjectPtr<UITT_FadeCommand>& Command)
{
	if(Command == nullptr)
	{
		return false;
	}

	if(ChangeSceneData.Step == EITT_ChangeSceneStep::Ready)
	{
		Command->OnFadeOutComplete = FITT_FadeEventDelegate::CreateWeakLambda(this, [this]()
			{
				ChangeSceneStep_LoadLevel();
			});
		
		FadeTool->Request(Command);
		return true;
	}
	return false;
}

bool UITT_SceneManager::ChangeSceneStep_LoadLevel()
{
	if(ChangeSceneData.LevelPackagePath == NAME_None)
	{
		ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));
		return true;
	}
	
	ChangeSceneData.Step = EITT_ChangeSceneStep::StartLoadLevel;

	//gCameraMng.ResetData();
	
	OnStartLevelLoading.Broadcast(ChangeSceneData.LevelPackagePath.ToString());

	return LoadLevelByPath(FITT_LoadLevelInitialized::CreateUObject(this, &UITT_SceneManager::OnCompleteLevelLoading), ChangeSceneData.LevelPackagePath, true);
}

void UITT_SceneManager::ChangeSceneStep_SetSceneState(uint8 SceneId)
{
	ChangeSceneData.Step = EITT_ChangeSceneStep::PrepareSceneState;

	if(SceneStateMachine)
	{
		SceneStateMachine->SetState(SceneId);
	}
}

void UITT_SceneManager::OnCompleteLevelLoading(const FString& LevelPackagePath)
{
	ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));

	OnFinishedLevelLoading.Broadcast(LevelPackagePath);
}
