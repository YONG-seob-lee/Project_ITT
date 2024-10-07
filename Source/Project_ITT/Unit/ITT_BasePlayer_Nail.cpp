// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer_Nail.h"

void UITT_BasePlayer_Nail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UITT_BasePlayer_Nail::PostInitialize()
{
	const TObjectPtr<AITT_CharacterBase> NailCharacter = GetCharacterBase();
	if(!NailCharacter)
	{
		return;
	}
	
	NailCharacter->SetActiveMovementComponent(false);
	NailCharacter->SetActiveProjectileMovementComponent(false);
	NailCharacter->SetProjectileUpdate();
}

void UITT_BasePlayer_Nail::Finalize()
{
	Super::Finalize();
}

void UITT_BasePlayer_Nail::AttachNail(USkeletalMeshComponent* OuterMesh, const FName& SocketName) const
{
	const TObjectPtr<AITT_CharacterBase> NailCh = GetCharacterBase();
	if(!NailCh)
	{
		return;
	}
	
	NailCh->AttachToComponent(OuterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}

void UITT_BasePlayer_Nail::DetachNail() const
{
	const TObjectPtr<AITT_CharacterBase> NailCh = GetCharacterBase();
	if(!NailCh)
	{
		return;
	}
	NailCh->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UITT_BasePlayer_Nail::Fire(const FVector& ShootDirection) const
{
	const TObjectPtr<AITT_CharacterBase> NailCharacter = GetCharacterBase();
	if(!NailCharacter)
	{
		return;
	}
	NailCharacter->SetActiveProjectileMovementComponent(true);
	NailCharacter->SetProjectileVelocity(ShootDirection);
}

TObjectPtr<USkeletalMeshComponent> UITT_BasePlayer_Nail::GetNailMesh() const
{
	const TObjectPtr<AITT_CharacterBase> NailCh = GetCharacterBase();
	if(!NailCh)
	{
		return nullptr;
	}

	return NailCh->GetSkeletalMeshComponent();
}
