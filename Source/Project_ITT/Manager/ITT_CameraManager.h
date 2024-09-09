// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "ITT_CameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_CameraManager : public UObject, public UITT_Singleton<UITT_CameraManager>
{
	GENERATED_BODY()
public:
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float _DeltaTime) override;

	void RegisterCameras();

	// step1. Activate Camera State
	void ChangeCamera(uint8 Index, bool bInstant = true) const;

	// step2. Valid Check Has Camera Actor 
	bool HasCamera(EITT_GameCameraType CameraType) const;
	
	// step2. Create Camera Actor
	TObjectPtr<class AITT_Actor_Camera> CreateCameraActor(const TSubclassOf<AITT_Actor_Camera>& CameraActorType, EITT_GameCameraType _CameraType);
	
	// step3. Activate Camera Actor
	TObjectPtr<AITT_Actor_Camera> ActiveCamera(EITT_GameCameraType _CameraType, float BlendTime = 0.f);

	TObjectPtr<AITT_Actor_Camera> GetActiveCamera();
private:
	void RegistCameraState(uint8 Index, const FName& Name, const TSubclassOf<class UITT_StateBase>& SceneType);

	void AddCameraActor(const FString& CameraType, TObjectPtr<AITT_Actor_Camera> CameraActor);
	
	UPROPERTY()
	TObjectPtr<class UITT_StateMachine> CameraStateMachine = nullptr;

	FString CurrentActiveType;
	TMap<FString, TObjectPtr<class AITT_Actor_Camera>> CameraActors;
	
#define gCameraMng (*UITT_CameraManager::GetInstance())
};
