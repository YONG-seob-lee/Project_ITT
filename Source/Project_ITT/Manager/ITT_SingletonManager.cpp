// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SingletonManager.h"

#include "ITT_CameraManager.h"
#include "ITT_InputManager.h"
#include "ITT_SceneManager.h"
#include "ITT_Singleton.h"
#include "ITT_TableManager.h"
#include "ITT_UnitManager.h"
#include "ITT_WidgetManager.h"
#include "../ITT_Define.h"

TObjectPtr<UITT_SingletonManager> UITT_SingletonManager::Instance = nullptr;

TObjectPtr<UITT_SingletonManager> UITT_SingletonManager::CreateInstance()
{
	Instance = ITT_NewObject<UITT_SingletonManager>();
	Instance->AddToRoot();
	Instance->RegisterSingletons();
	return Instance;
}

void UITT_SingletonManager::DestroyInstance()
{
	if (IsValid(Instance))
	{
		Instance->RemoveSingletons();
		Instance->RemoveFromRoot();
		ITT_DeleteObject(Instance);
		Instance = nullptr;
	}
}

void UITT_SingletonManager::BuiltInInitializeSingletons()
{
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->BuiltInInitialize();
	}

	bIsBuiltInInitialized = true;
}

void UITT_SingletonManager::TickSingletons(float DeltaTime)
{
	if (bInitialized)
	{
		for (ISingleton* Singleton : Singletons)
		{
			Singleton->Tick(DeltaTime);
		}
	}
}

void UITT_SingletonManager::RemoveSingletons()
{
	Singletons.Empty();
	
	//  매니저 제거
	UITT_TableManager::RemoveInstance();
	UITT_SceneManager::RemoveInstance();
	UITT_WidgetManager::RemoveInstance();
	UITT_InputManager::RemoveInstance();
	UITT_CameraManager::RemoveInstance();
	UITT_UnitManager::RemoveInstance();
}

void UITT_SingletonManager::InitializeSingletons()
{
	if(bInitialized)
	{
		return;
	}
    
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->Initialize();
	}

	bInitialized = true;
}

void UITT_SingletonManager::FinalizeSingletons()
{
	if (bInitialized == false)
	{
		return;
	}

	for (ISingleton* Singleton : Singletons)
	{
		Singleton->PreFinalize();
		Singleton->Finalize();
		Singleton->BuiltInFinalize();
	}
}

void UITT_SingletonManager::RegisterSingletons()
{
    Singletons.Reset();

	// 매니저 추가.
	Singletons.Emplace(UITT_TableManager::MakeInstance());
	Singletons.Emplace(UITT_SceneManager::MakeInstance());
	Singletons.Emplace(UITT_WidgetManager::MakeInstance());
	Singletons.Emplace(UITT_InputManager::MakeInstance());
	Singletons.Emplace(UITT_CameraManager::MakeInstance());
	Singletons.Emplace(UITT_UnitManager::MakeInstance());
}
