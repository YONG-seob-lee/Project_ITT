// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_InstUtil.h"

#include "EngineUtils.h"
#include "ITT_PlayerController.h"
#include "Actor/SpawnPoint/ITT_PlayerSpawnPoint_Cody.h"
#include "Actor/SpawnPoint/ITT_PlayerSpawnPoint_May.h"
#include "Actor/SpawnPoint/ITT_PlayerSpawnPoint_Rose.h"
#include "Character/ITT_CharacterBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"

TObjectPtr<UITT_InstUtil> UITT_InstUtil::ThisInstance = nullptr;
FStreamableManager UITT_InstUtil::AssetLoader;

void UITT_InstUtil::Initialize(TObjectPtr<UITT_GameInstance> _GameInstance)
{
	GameInstance = _GameInstance;
}

void UITT_InstUtil::Finalize()
{
	GameInstance = nullptr;
}

float UITT_InstUtil::GetAspectRatio()
{
	return GetGameViewport()->GetDesiredAspectRatio();
}

void UITT_InstUtil::ShowMessageOnScreen(const FString& Message, bool bNewerOnTop, float ElapsedTime, FColor DisplayColor)
{
	GEngine->AddOnScreenDebugMessage(-1, ElapsedTime, DisplayColor, Message);
}

TObjectPtr<UWorld> UITT_InstUtil::GetGameWorld()
{
	return ThisInstance->GameInstance->GetWorld();
}

TObjectPtr<UITT_GameInstance> UITT_InstUtil::GetGameInstance()
{
	return ThisInstance->GameInstance == nullptr ? nullptr : ThisInstance->GameInstance;
}

TObjectPtr<APlayerController> UITT_InstUtil::GetPlayerController()
{
	const TObjectPtr<UWorld> World = GetGameWorld();
	if(World == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<APlayerController> Controller = UGameplayStatics::GetPlayerController(World, 0);
	
	return Controller ? Controller : nullptr;
}

FSceneViewport* UITT_InstUtil::GetGameViewport()
{
	if(GEngine && GEngine->GameViewport)
	{
		return GEngine->GameViewport->GetGameViewport();
	}

	return nullptr;
}

bool UITT_InstUtil::HasGameInstance()
{
	return ThisInstance->GameInstance != nullptr;
}

FString UITT_InstUtil::GetBPNameFromFullPath(const FString& FullPath)
{
	if(FullPath.IsEmpty())
	{
		return FString();
	}

	int32 LastPoint = 0;
	int32 LastSlash = 0;
	constexpr TCHAR Point = '.';
	constexpr TCHAR Slash = '/';
	FullPath.FindLastChar(Point, LastPoint);
	FullPath.FindLastChar(Slash, LastSlash);

	return FullPath.Mid(LastSlash + 1, LastPoint - LastSlash - 1);	
}

TObjectPtr<AActor> UITT_InstUtil::SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation,
                                             const FString& LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent)
{
	const TObjectPtr<UWorld> World = GetGameWorld();

	if (World == nullptr || Class == nullptr)
	{
		return nullptr;
	}
	AActor* NewActor = nullptr;
	
	FActorSpawnParameters Params;
	Params.OverrideLevel = World->GetCurrentLevel();
	Params.SpawnCollisionHandlingOverride = CollisionMathod;
	NewActor = World->SpawnActor(Class, &Location, &Rotation, Params);
	if (NewActor)
	{
#if WITH_EDITOR
		if (LabelName.IsEmpty() == false)
			NewActor->SetActorLabel(LabelName);
#endif

		if ((bNeedRootComponent == true) && (NewActor->GetRootComponent() == nullptr))
		{
			USceneComponent* RootComponent = NewObject<USceneComponent>(NewActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;
#if WITH_EDITORONLY_DATA
			RootComponent->bVisualizeComponent = false;
#endif
			NewActor->SetRootComponent(RootComponent);
			NewActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return NewActor;
}

TObjectPtr<AITT_PlayerSpawnPoint> UITT_InstUtil::GetSpawnPoint(FName CharacterName)
{
	const TObjectPtr<UWorld> World = GetGameWorld();
	for(TActorIterator<AActor> Iter(World); Iter; ++Iter)
	{
		if(CharacterName == CharacterName::Cody)
		{
			if(const TObjectPtr<AITT_PlayerSpawnPoint_Cody> CodySpawnPoint = Cast<AITT_PlayerSpawnPoint_Cody>(*Iter))
			{
				return CodySpawnPoint;
			}
		}
		else if(CharacterName == CharacterName::May)
		{
			if(const TObjectPtr<AITT_PlayerSpawnPoint_May> MaySpawnPoint = Cast<AITT_PlayerSpawnPoint_May>(*Iter))
			{
				return MaySpawnPoint;
			}
		}
		else if(CharacterName == CharacterName::Rose)
		{
			if(const TObjectPtr<AITT_PlayerSpawnPoint_Rose> RoseSpawnPoint = Cast<AITT_PlayerSpawnPoint_Rose>(*Iter))
			{
				return RoseSpawnPoint;
			}	
		}
	}

	return nullptr;
}

TObjectPtr<AActor> UITT_InstUtil::SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent /* = true */, 
															 ESpawnActorCollisionHandlingMethod Method /* = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn */)
{
	UClass* BlueprintClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BlueprintPath);
	if(IsValid(BlueprintClass) == false)
	{
		ITT_CHECK(false);
		ITT_LOG(TEXT("Blueprint Path or Name is not Correct. Please Check Blueprint Path"));
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = GetGameWorld();
	if(IsValid(World) == false)
	{
		return nullptr;	
	}
			
	FActorSpawnParameters Parameters;
	Parameters.OverrideLevel = World->GetCurrentLevel();
	Parameters.SpawnCollisionHandlingOverride = Method;
	const TObjectPtr<AActor> ResultActor = World->SpawnActor(BlueprintClass, &Pos, &Rot, Parameters);

	if(ResultActor)
	{
		ResultActor->SetActorLabel(GetBPNameFromFullPath(BlueprintPath));

		if(bNeedRootComponent && ResultActor->GetRootComponent() == nullptr)
		{
			const TObjectPtr<USceneComponent> RootComponent = NewObject<USceneComponent>(ResultActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;

			ResultActor->SetRootComponent(RootComponent);
			ResultActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return ResultActor != nullptr ? ResultActor : nullptr;
}

void UITT_InstUtil::AssignUnitHandle(ITT_Handle _UnitHandle)
{
	if(const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(GetPlayerController()))
	{
		PlayerController->SetUnitHandle(_UnitHandle);
	}	
}

void UITT_InstUtil::OnPossessUnit(const TObjectPtr<AITT_CharacterBase>& CharacterBase)
{
	if(const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(GetPlayerController()))
	{
		PlayerController->Possess(CharacterBase);
	}
}

void UITT_InstUtil::FlushPressedKeys()
{
	if(GetGameWorld())
	{
		if(const TObjectPtr<APlayerController> PlayerController = GetPlayerController())
		{
			PlayerController->FlushPressedKeys();
		}
	}
}

TObjectPtr<UObject> UITT_InstUtil::LoadObjectFromFile(const FString& ResourcePath, const FITT_LoadResourceDelegate& Delegate, const FString& SubName, int32 Index, bool SubBool)
{
	const FSoftObjectPath Reference = FSoftObjectPath(ResourcePath);
	
	UObject* ResultObject = AssetLoader.LoadSynchronous(Reference);
	if(Delegate.IsBound())
	{
		Delegate.Execute(ResourcePath, ResultObject);
	}
	return ResultObject;
}
