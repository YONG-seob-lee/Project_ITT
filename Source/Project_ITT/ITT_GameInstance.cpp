// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_GameInstance.h"
#include "ITT_InstUtil.h"
#include "GameMode/ITT_GameViewportClient.h"
#include "Manager/ITT_CameraManager.h"
#include "Manager/ITT_InputManager.h"
#include "Manager/ITT_SceneManager.h"
#include "Manager/ITT_SingletonManager.h"
#include "Manager/ITT_UnitManager.h"
#include "Unit/ITT_UnitBase.h"

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
		gInputMng.PostInitialize();
		bExecuteLodeLevel = false;
	}
	
	return true;
}

void UITT_GameInstance::HandleInputDeviceConnectionChange(EInputDeviceConnectionState NewConnectionState,
	FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId)
{
	Super::HandleInputDeviceConnectionChange(NewConnectionState, PlatformUserId, InputDeviceId);

	SplitScreen(InputDeviceId.GetId());

	if(InputDeviceId.GetId() == 1)
	{
		if(NewConnectionState == EInputDeviceConnectionState::Connected)
		{
			const TArray<ULocalPlayer*> Players = GetLocalPlayers();
			if(Players.Num() == 2)
			{
				// if(Players.IsValidIndex(0))
				// {
				// 	if(const TObjectPtr<UITT_UnitBase> CodyUnit = gUnitMng.GetUnitTableId(ITT_Character::Cody))
				// 	{
				// 		Players[0]->PlayerController->Possess(CodyUnit->GetCharacterBase());
				//
				// 	}
				// }

				if(Players.IsValidIndex(1))
				{
					if(const TObjectPtr<UITT_UnitBase> MayUnit = gUnitMng.GetUnitTableId(ITT_Character::May))
					{
						Players[1]->PlayerController->Possess(MayUnit->GetCharacterBase());
						ITT_LOG(TEXT("asdf"));
					}
				}
			}

			if(UITT_InstUtil::GetCurrentSceneType() <= EITT_GameSceneType::Title)
			{
				SplitScreen(ESplitScreenType::None);
			}
			else
			{
				SplitScreen(ESplitScreenType::TwoPlayer_Vertical);
			}
		}
		else if(NewConnectionState == EInputDeviceConnectionState::Disconnected)
		{
			//Pause
			SplitScreen(ESplitScreenType::None);
		}
		EITT_GameSceneType CurrentSceneType =UITT_InstUtil::GetCurrentSceneType();
	}
}

void UITT_GameInstance::HandleInputDevicePairingChange(FInputDeviceId InputDeviceId, FPlatformUserId NewUserPlatformId,
	FPlatformUserId OldUserPlatformId)
{
	Super::HandleInputDevicePairingChange(InputDeviceId, NewUserPlatformId, OldUserPlatformId);
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

void UITT_GameInstance::SplitScreen(int32 InputDeviceId) const
{
	if(InputDeviceId == 1)
	{
		UITT_GameViewportClient* GameViewportClient = Cast<UITT_GameViewportClient>(GetGameViewportClient());
		if(!GameViewportClient)
		{
			return;
		}
		GameViewportClient->UpdateActiveSplitscreenType();
	
		// FString OutError;
		// ULocalPlayer* NewLocalPlayer = CreateLocalPlayer(InputDeviceId, OutError, true);
		//
		// const TArray<ULocalPlayer*> LPS = GetLocalPlayers();
	}
}

void UITT_GameInstance::SplitScreen(ESplitScreenType::Type ScreenType) const
{
	UITT_GameViewportClient* GameViewportClient = Cast<UITT_GameViewportClient>(GetGameViewportClient());
	if(!GameViewportClient)
	{
		return;
	}
	GameViewportClient->UpdateActiveSplitScreenType(ScreenType);
}
