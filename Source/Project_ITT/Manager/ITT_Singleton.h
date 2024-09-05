// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ISingleton
{
public:
	virtual ~ISingleton() {}

	/////// INITIALIZE STEP
	// step 1. Before Initialize 'Pre-Init'(선작업)
	virtual void BuiltInInitialize() {}

	// step 2. Basic Initialize
	virtual void Initialize() {}

	// step 3. After Initialize 'Post-Init'(후작업)
	virtual void PostInitialize() {}


	/////// FINISH STEP
	// step 1. Before Finalize 'Pre-Fin'(선작업)
	virtual void PreFinalize() {}
	
	// step 2. Basic Finalize
	virtual void Finalize() {}
	
	// step 3. After Finalize 'Post-Fin'(후작업)
	virtual void BuiltInFinalize() {}

	
	virtual void Tick(float _DeltaTime) {}
};

/**
 *
 */
template<typename TClass>
class PROJECT_ITT_API UITT_Singleton : public ISingleton
{
protected:
	static TObjectPtr<TClass> Instance;

public:
	static TClass* MakeInstance();
	static void    RemoveInstance();
	static TObjectPtr<TClass> GetInstance();
	static bool    HasInstance();
};


template<typename TClass>
TObjectPtr<TClass> UITT_Singleton<TClass>::Instance = nullptr;

#include "ITT_Singleton.inl"
