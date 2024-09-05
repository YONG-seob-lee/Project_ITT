// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_PlayerSpawnPoint_Rose.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AITT_PlayerSpawnPoint_Rose::AITT_PlayerSpawnPoint_Rose()
{
#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
		FName Id_SpawnNpcActor;
		FText Name_SpawnNpcActor;

		FConstructorStatics() : TextureFinder(*DefaultImage::PortraitPath_Rose),
								Id_SpawnNpcActor(DefaultImage::Name),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "DefaultImage", "DefaultImage")) {}
	};
	
	if (!IsRunningCommandlet())
	{
		if (const TObjectPtr<UBillboardComponent> _SpriteComponent = GetGoodSprite())
		{
			FConstructorStatics ConstructorStatics;
			_SpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
			_SpriteComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
			_SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
		}

		if (const TObjectPtr<UArrowComponent> _ArrowComponent = GetArrowComponent())
		{
			_ArrowComponent->ArrowSize = 5.f;
		}
	}

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if(!Capsule)
	{
		return;
	}

	Capsule->InitCapsuleSize(10.f, 10.f);
#endif
	SpawnName = FName("Rose");
}

// Called when the game starts or when spawned
void AITT_PlayerSpawnPoint_Rose::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AITT_PlayerSpawnPoint_Rose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

