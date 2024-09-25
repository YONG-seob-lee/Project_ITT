// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer_Nail.h"

void UITT_BasePlayer_Nail::AttachNail(USkeletalMeshComponent* OuterMesh, const FName& SocketName) const
{
	const TObjectPtr<USkeletalMeshComponent> NailMeshComponent = GetNailMesh();
	if(!NailMeshComponent)
	{
		return;
	}

	NailMeshComponent->AttachToComponent(OuterMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

TObjectPtr<USkeletalMeshComponent> UITT_BasePlayer_Nail::GetNailMesh() const
{
	const TObjectPtr<AITT_CharacterBase> NailCh = GetCharacterBase();
	if(!NailCh)
	{
		return nullptr;
	}

	return NailCh->GetRootSkeletalMeshComponent();
}
