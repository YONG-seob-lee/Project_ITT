// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ITT_SingletonManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SingletonManager : public UObject
{
	GENERATED_BODY()
public:
	static TObjectPtr<UITT_SingletonManager> CreateInstance();
	static void DestroyInstance();
	static TObjectPtr<UITT_SingletonManager> GetInstance() { return Instance; }


	void BuiltInInitializeSingletons();
	void TickSingletons(float DeltaTime);

	void RemoveSingletons();
	
	void InitializeSingletons();
	void FinalizeSingletons();

protected:
	static TObjectPtr<UITT_SingletonManager> Instance;

private:

	void RegisterSingletons();

	bool bIsBuiltInInitialized = false;
	bool bInitialized = false;
	TArray<class ISingleton*> Singletons;
};
