// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer_Doll.h"

TObjectPtr<USkeletalMeshComponent> UITT_BasePlayer_Doll::GetSkeletalMeshComponent() const
{
	if(!CharacterBase.IsValid())
	{
		return nullptr;
	}

	return CharacterBase->GetRootSkeletalMeshComponent();
}
