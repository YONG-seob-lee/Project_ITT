// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_GameInstance.h"
#include "UObject/Object.h"
#include "ITT_Define.h"
#include "Engine/StreamableManager.h"
#include "CommonInputSubsystem.h"
#include "ITT_InstUtil.generated.h"

namespace CharacterName
{
	const FName Cody = TEXT("Cody");
	const FName May = TEXT("May");
	const FName Rose = TEXT("Rose");
	const FName Dummy = TEXT("Dummy");
}

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_InstUtil : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(TObjectPtr<UITT_GameInstance> _GameInstance);
	void Finalize();

	FORCEINLINE FStreamableManager& GetAssetLoader() { return AssetLoader; }
	static float GetAspectRatio();

	static EITT_GameSceneType GetCurrentSceneType();

	static void ShowMessageOnScreen(const FString& Message, bool bNewerOnTop = true, float ElapsedTime = 3.f, FColor DisplayColor = FColor::Green);

	static TObjectPtr<UWorld> GetGameWorld();
	static TObjectPtr<UITT_GameInstance> GetGameInstance();
	static TObjectPtr<APlayerController> GetPlayerController(int32 PlayerIndex = 0);
	static FSceneViewport* GetGameViewport();
	static bool HasGameInstance();

	static FString GetBPNameFromFullPath(const FString& FullPath);

	static TObjectPtr<AActor> SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString &LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent);
	
	static TObjectPtr<class AITT_PlayerSpawnPoint> GetSpawnPoint(FName CharacterName);

	static TObjectPtr<AActor> SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent = true,
													  ESpawnActorCollisionHandlingMethod Method = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	
	static void AssignUnitHandle(ITT_Handle _UnitHandle);
	static void OnPossessUnit(const TObjectPtr<class AITT_CharacterBase>& CharacterBase, int32 PlayerIndex = 0);

	static void FlushPressedKeys();
	
	static TObjectPtr<UDataTable> LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, const FITT_LoadResourceDelegate& Delegate)
	{
		const TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ResourcePath, *ResourcePath, LOAD_None, nullptr));

		if(Delegate.IsBound())
		{
			Delegate.Execute(TableName, ResultObject);
		}
	
		return ResultObject;
	}

	static TObjectPtr<UObject> LoadObjectFromFile(const FString& ResourcePath, const FITT_LoadResourceDelegate& Delegate = nullptr, const FString& SubName = TEXT("SubName"), int32 Index = 0, bool SubBool = false);

	// todo 용섭 : Enum 을 FString 으로 변환하는 메소드
	template<typename TEnum>
	static FString ConvertEnumToString(const FString& EnumString, TEnum EnumType)
	{
		const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumString);
		if (!pEnum)
		{
			return FString("");
		}

		const int32 Index = pEnum->GetIndexByValue(static_cast<int32>(EnumType));
		return pEnum->GetNameStringByIndex(Index);
	}

	template<typename TEnum>
static FName ConvertEnumToName(const FString& EnumString, TEnum EnumType)
	{
		const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumString);
		if (!pEnum)
		{
			return FName("");
		}

		const int32 Index = pEnum->GetIndexByValue(static_cast<int32>(EnumType));
		return pEnum->GetNameByValue(Index);
	}
	
private:
	
	static TObjectPtr<UITT_InstUtil> ThisInstance;

	UPROPERTY()
	TObjectPtr<UITT_GameInstance> GameInstance = nullptr;
	
	static FStreamableManager AssetLoader;















public:
	static TObjectPtr<UITT_InstUtil> MakeInstance()
	{
		if(ThisInstance == nullptr)
		{
			ThisInstance = ITT_NewObject<UITT_InstUtil>();
			ThisInstance->AddToRoot();
		}
		return ThisInstance;
	}
	static void RemoveInstance()
	{
		if(ThisInstance != nullptr)
		{
			ThisInstance->RemoveFromRoot();
			ThisInstance->ConditionalBeginDestroy();
			ThisInstance = nullptr;
		}
	}
	static bool HasInstance()
	{
		return ThisInstance != nullptr;
	}
	static TObjectPtr<UITT_InstUtil> GetInstance()
	{
		return ThisInstance == nullptr ? nullptr : ThisInstance;
	}
};
