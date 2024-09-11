// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Engine/GameInstance.h"
#include "ITT_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UITT_GameInstance();
	virtual ~UITT_GameInstance() override;

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	
	bool Tick(float DeltaSeconds);

private:
	void OnStartGameInstance(UGameInstance* GameInstance);
	
	void Initialize();
	void Finalize();
	
	void Init_CreateManager();
	void Init_RegisterTick();
	void Init_RegisterState();
	void Init_LoadBaseWorld();

	void Finish_Manager();
	void Finish_Tick();
	void Finish_World();

	void SplitScreen();
	
	FTSTicker::FDelegateHandle TickDelegateHandle;
	
	UPROPERTY(Category = UITT_GameInstance, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> BaseWorld;
	
	bool bInitialized = false;
	bool bExecuteLodeLevel = false;
};
