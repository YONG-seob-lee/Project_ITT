// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SceneBase.h"

void UITT_SceneBase::Begin()
{
	Super::Begin();

	LoadingProcessDelegates.Empty();
	LoadingProcessDelegates.Add(FITT_LoadingProcessDelegate::CreateUObject(this, &UITT_SceneBase::LoadingPreProcess));
	LoadingProcessDelegates.Add(FITT_LoadingProcessDelegate::CreateUObject(this, &UITT_SceneBase::LoadingProcess));
	LoadingProcessDelegates.Add(FITT_LoadingProcessDelegate::CreateUObject(this, &UITT_SceneBase::LoadingPostProcess));
}

void UITT_SceneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_SceneBase::Exit()
{
	Super::Exit();

	LoadingProcessDelegates.Empty();
}

void UITT_SceneBase::TickLoading(float DeltaTime)
{
	if (LoadingProcessDelegates.IsValidIndex(0) == true)
	{
		if (LoadingProcessDelegates[0].Execute(DeltaTime) == true)
		{
			LoadingProcessDelegates.RemoveAt(0);
		}
	}
}

bool UITT_SceneBase::IsCompleteLoading()
{
	return LoadingProcessDelegates.Num() <= 0;
}

bool UITT_SceneBase::LoadingPreProcess(float DeltaTime)
{
	return true;
}

bool UITT_SceneBase::LoadingProcess(float DeltaTime)
{
	return true;
}

bool UITT_SceneBase::LoadingPostProcess(float DeltaTime)
{
	return true;
}
