// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_GameInstance.h"
#include "ITT_InstUtil.h"
#include "Manager/ITT_CameraManager.h"
#include "Manager/ITT_SceneManager.h"
#include "Manager/ITT_SingletonManager.h"

UITT_GameInstance::UITT_GameInstance()
{
	FWorldDelegates::OnStartGameInstance.AddUObject(this, &UITT_GameInstance::OnStartGameInstance);

	TickDelegateHandle = nullptr;
}

UITT_GameInstance::~UITT_GameInstance()
{
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
}

void UITT_GameInstance::Init()
{
	Super::Init();

	Initialize();
}

void UITT_GameInstance::Shutdown()
{
	Finalize();
	
	Super::Shutdown();
}

void UITT_GameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	gSceneMng.SceneLoadComplete(LoadTime, MapName);
}

bool UITT_GameInstance::Tick(float DeltaSeconds)
{
	if(bInitialized == false)
	{
		return false;
	}

	if(const TObjectPtr<UITT_SingletonManager> SingletonManager = UITT_SingletonManager::GetInstance())
	{
		SingletonManager->TickSingletons(DeltaSeconds);
	}

	if(bExecuteLodeLevel)
	{
		gSceneMng.ExecuteLoadLevelDelegate();
		bExecuteLodeLevel = false;
	}
	
	return true;
}

void UITT_GameInstance::OnStartGameInstance(UGameInstance* GameInstance)
{
	if (UITT_SingletonManager* SingletonManager = UITT_SingletonManager::GetInstance())
	{
		SingletonManager->InitializeSingletons();
	}
}

void UITT_GameInstance::Initialize()
{
	Init_CreateManager();
	Init_RegisterTick();
	Init_RegisterState();
	Init_LoadBaseWorld();

	bExecuteLodeLevel = true;
	bInitialized = true;
}

void UITT_GameInstance::Finalize()
{
	Finish_Manager();
	Finish_Tick();
}

void UITT_GameInstance::Init_CreateManager()
{
	if(const TObjectPtr<UITT_InstUtil> BasicGameUtility = UITT_InstUtil::MakeInstance())
	{
		BasicGameUtility->Initialize(this);
	}

	if(const TObjectPtr<UITT_SingletonManager> SingletonManager = UITT_SingletonManager::CreateInstance())
	{
		SingletonManager->BuiltInInitializeSingletons();
	}
}

void UITT_GameInstance::Init_RegisterTick()
{
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UITT_GameInstance::Tick));
}

void UITT_GameInstance::Init_RegisterState()
{
	ITT_CHECK(UITT_SceneManager::HasInstance());

	gSceneMng.RegisterSceneStates();
	gCameraMng.RegisterCameras();
}

void UITT_GameInstance::Init_LoadBaseWorld()
{
	if(BaseWorld.IsValid())
	{
		gSceneMng.LoadLevelBySoftObjectPtr(BaseWorld, FITT_LoadLevelInitialized::CreateWeakLambda(this, [this](const FString& Value)
		{
			gSceneMng.ChangeScene(EITT_GameSceneType::Logo);
		}));
	}
}

void UITT_GameInstance::Finish_Manager()
{
	if(const TObjectPtr<UITT_InstUtil> BasicGameUtility = UITT_InstUtil::GetInstance())
	{
		BasicGameUtility->Finalize();
		BasicGameUtility->RemoveInstance();
	}
	
	if (UITT_SingletonManager* SingletonManager = UITT_SingletonManager::GetInstance())
	{
		SingletonManager->FinalizeSingletons();
	}

	UITT_SingletonManager::DestroyInstance();
}

void UITT_GameInstance::Finish_Tick()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

void UITT_GameInstance::Finish_World()
{
	if(BaseWorld.IsValid())
	{
		BaseWorld = nullptr;
	}
}