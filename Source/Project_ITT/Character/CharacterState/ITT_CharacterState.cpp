// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CharacterState.h"

void UITT_CharacterState::Initialize(uint8 Index, const FName& Name)
{
	Super::Initialize(Index, Name);

	CharacterState = static_cast<EITT_CharacterState>(Index);
}

void UITT_CharacterState::Finalize()
{
	Super::Finalize();
}
