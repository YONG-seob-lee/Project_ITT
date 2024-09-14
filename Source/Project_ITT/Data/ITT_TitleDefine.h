// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ITT_Player : uint32
{
	None = 0,
	First = 1,
	Second = 2,
};

UENUM(BlueprintType)
enum class EITT_SelectCharacter : uint8
{
	None = 0,
	Cody = 1,
	May = 2,
	Both = 3,
};

enum class EITT_JoyStick : uint32
{
	None = 0,
	Keyboard,
	GamePad,
};

struct FITT_PlayerData
{
public:
	FITT_PlayerData():CharacterPos(EITT_SelectCharacter::None), JoyStick(EITT_JoyStick::None) {}
	
	FORCEINLINE EITT_SelectCharacter GetPosition() const { return CharacterPos; }
	FORCEINLINE void SetPosition(EITT_SelectCharacter _Pos) { CharacterPos = _Pos; }

	FORCEINLINE EITT_JoyStick GetJoyStick() const { return JoyStick; }
	FORCEINLINE void SetJoyStick(EITT_JoyStick _JoyStick) { JoyStick = _JoyStick; }
private:
	EITT_SelectCharacter CharacterPos = EITT_SelectCharacter::None;
	EITT_JoyStick JoyStick = EITT_JoyStick::None;
};

struct FITT_ResultSelectData
{
public:
	FITT_ResultSelectData():bChanged(false),Player(ITT_Player::None),PrevPosition(EITT_SelectCharacter::None),NextPosition(EITT_SelectCharacter::None) {}
	FITT_ResultSelectData(ITT_Player _Player, EITT_SelectCharacter _PrevPosition):bChanged(false),Player(_Player),PrevPosition(_PrevPosition),NextPosition(EITT_SelectCharacter::None) {}

	bool bChanged;
	ITT_Player Player;
	EITT_SelectCharacter PrevPosition;
	EITT_SelectCharacter NextPosition;
};


struct FITT_SelectData
{
	FITT_SelectData() {}
	
	FITT_ResultSelectData SetPlayerData(ITT_Player _Player, bool bMoveRight);

	bool IsAllExist() const;
	FORCEINLINE bool IsExistCody() const { return bExistCody; }
	FORCEINLINE bool IsExistMay() const { return bExistMay; }
private:
	bool bExistMay = false;
	bool bExistCody = false;

	FITT_PlayerData FirstSelectedData;
	FITT_PlayerData SecondSelectedData;
};