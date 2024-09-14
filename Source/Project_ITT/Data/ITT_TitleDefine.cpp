// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_TitleDefine.h"

FITT_ResultSelectData FITT_SelectData::SetPlayerData(ITT_Player _Player, bool bMoveRight)
{
	FITT_ResultSelectData ResultData = FITT_ResultSelectData(_Player, _Player == ITT_Player::First ? FirstSelectedData.GetPosition() : SecondSelectedData.GetPosition());
	
	if(_Player == ITT_Player::First)
	{
		if(bMoveRight)
		{
			if(ResultData.PrevPosition == EITT_SelectCharacter::May)
			{
				ResultData.NextPosition = EITT_SelectCharacter::None;
				FirstSelectedData.SetPosition(EITT_SelectCharacter::None);
				bExistMay = false;
				ResultData.bChanged = true;
			}
			else if(ResultData.PrevPosition == EITT_SelectCharacter::Cody)
			{
				ResultData.NextPosition = EITT_SelectCharacter::Cody;
			}
			else
			{
				if(bExistCody)
				{
					ResultData.NextPosition = EITT_SelectCharacter::None;
				}
				else
				{
					ResultData.NextPosition = EITT_SelectCharacter::Cody;
					FirstSelectedData.SetPosition(EITT_SelectCharacter::Cody);
					bExistCody = true;
					ResultData.bChanged = true;
				}
			}
		}
		else
		{
			if(ResultData.PrevPosition == EITT_SelectCharacter::Cody)
			{
				ResultData.NextPosition = EITT_SelectCharacter::None;
				FirstSelectedData.SetPosition(EITT_SelectCharacter::None);
				bExistCody = false;
				ResultData.bChanged = true;
			}
			else if(ResultData.PrevPosition == EITT_SelectCharacter::May)
			{
				ResultData.NextPosition = EITT_SelectCharacter::May;
			}
			else
			{
				if(bExistMay)
				{
					ResultData.NextPosition = EITT_SelectCharacter::None;
				}
				else
				{
					ResultData.NextPosition = EITT_SelectCharacter::May;
					FirstSelectedData.SetPosition(EITT_SelectCharacter::May);
					bExistMay = true;
					ResultData.bChanged = true;
				}
			}
		}
	}
	else
	{
		if(bMoveRight)
		{
			if(ResultData.PrevPosition == EITT_SelectCharacter::May)
			{
				ResultData.NextPosition = EITT_SelectCharacter::None;
				SecondSelectedData.SetPosition(EITT_SelectCharacter::None);
				bExistMay = false;
				ResultData.bChanged = true;
			}
			else if(ResultData.PrevPosition == EITT_SelectCharacter::Cody)
			{
				ResultData.NextPosition = EITT_SelectCharacter::Cody;
			}
			else
			{
				if(bExistCody)
				{
					ResultData.NextPosition = EITT_SelectCharacter::None;
				}
				else
				{
					ResultData.NextPosition = EITT_SelectCharacter::Cody;
					SecondSelectedData.SetPosition(EITT_SelectCharacter::Cody);
					bExistCody = true;
					ResultData.bChanged = true;
				}
			}
		}
		else
		{
			if(ResultData.PrevPosition == EITT_SelectCharacter::Cody)
			{
				ResultData.NextPosition = EITT_SelectCharacter::None;
				SecondSelectedData.SetPosition(EITT_SelectCharacter::None);
				bExistCody = false;
				ResultData.bChanged = true;
			}
			else if(ResultData.PrevPosition == EITT_SelectCharacter::May)
			{
				ResultData.NextPosition = EITT_SelectCharacter::May;
			}
			else
			{
				if(bExistMay)
				{
					ResultData.NextPosition = EITT_SelectCharacter::None;
				}
				else
				{
					ResultData.NextPosition = EITT_SelectCharacter::May;
					SecondSelectedData.SetPosition(EITT_SelectCharacter::May);
					bExistMay = true;
					ResultData.bChanged = true;
				}
			}
		}
	}

	return ResultData;
}

bool FITT_SelectData::IsAllExist() const
{
	if(bExistCody && bExistMay)
	{
		return true;
	}

	return false;
}
