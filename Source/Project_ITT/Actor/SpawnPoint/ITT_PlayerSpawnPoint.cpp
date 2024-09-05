// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_PlayerSpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

// AITT_PlayerSpawnPoint::AITT_PlayerSpawnPoint(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
// {
// #if WITH_EDITORONLY_DATA
// 	struct FConstructorStatics
// 	{
// 		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
// 		FName Id_SpawnNpcActor;
// 		FText Name_SpawnNpcActor;
//
// 		FConstructorStatics() : TextureFinder(*DefaultImage::PortraitPath_Cody),
// 								Id_SpawnNpcActor(DefaultImage::Name),
// 								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "DefaultImage", "DefaultImage")) {}
// 	};
// 	
// 	if (!IsRunningCommandlet())
// 	{
// 		if (const TObjectPtr<UBillboardComponent> _SpriteComponent = GetGoodSprite())
// 		{
// 			FConstructorStatics ConstructorStatics;
// 			_SpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
// 			_SpriteComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
// 			_SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
// 		}
//
// 		if (const TObjectPtr<UArrowComponent> _ArrowComponent = GetArrowComponent())
// 		{
// 			_ArrowComponent->ArrowSize = 5.f;
// 		}
// 	}
// #endif
// }