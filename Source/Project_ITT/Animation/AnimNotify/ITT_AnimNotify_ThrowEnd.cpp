﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_AnimNotify_ThrowEnd.h"

#include "ITT_InstUtil.h"
#include "ITT_PlayerController.h"
#include "Manager/ITT_UnitManager.h"
#include "Unit/ITT_BasePlayer_Cody.h"
#include "Unit/ITT_UnitBase.h"

void UITT_AnimNotify_ThrowEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(UITT_InstUtil::GetPlayerController()))
	{
		if(const TObjectPtr<UITT_BasePlayer_Cody> CodyUnit = Cast<UITT_BasePlayer_Cody>(gUnitMng.GetUnitTableId(ITT_Character::Cody)))
		{
			CodyUnit->GetCharacterBase()->SetCharacterState(EITT_CharacterState::Aim);
			CodyUnit->ReloadNail();
		}
	}
}
