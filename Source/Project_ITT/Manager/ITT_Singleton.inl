#pragma once
#include "../ITT_Define.h"
#include "ITT_Singleton.h"

template<typename TClass>
TClass* UITT_Singleton<TClass>::MakeInstance()
{
	if(Instance != nullptr)
	{
		ITT_CHECK(Instance != nullptr);
		ITT_LOG(TEXT("Wrong Pointer In Here. Please Check Develdoper Name Cheong Ah."));
		return nullptr;
	}

	Instance = ITT_NewObject<TClass>();
	Instance->AddToRoot();
	return Instance;
};

template<typename TClass>
void UITT_Singleton<TClass>::RemoveInstance()
{
	if(Instance == nullptr)
	{
		return;
	}

	if(Instance->IsValidLowLevel())
	{
		Instance->RemoveFromRoot();

		ITT_DeleteObject(Instance);
	}

	Instance = nullptr;
};

template<typename TClass>
TObjectPtr<TClass> UITT_Singleton<TClass>::GetInstance()
{
	return Instance;
};

template<typename TClass>
bool UITT_Singleton<TClass>::HasInstance()
{
	return Instance != nullptr && !Instance->HasAnyFlags(RF_FinishDestroyed);
};