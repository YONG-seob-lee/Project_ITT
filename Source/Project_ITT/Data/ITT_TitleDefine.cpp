// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_TitleDefine.h"

FITT_ResultSelectData FITT_SelectData::SetPlayerData(ITT_Player _Player, bool bMoveRight)
{
	FITT_ResultSelectData ResultData = FITT_ResultSelectData(_Player, FirstSelectedData.GetPosition());
	
	if(_Player == ITT_Player::First)
	{
		if(bMoveRight)
		{
			if(ResultData.PrevPosition == EITT_SelectCharacter::May)
			{
				ResultData.NextPosition = EITT_SelectCharacter::None;
				FirstSelectedData.SetPosition(EITT_SelectCharacter::None);
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
					ResultData.bChanged = true;
				}
			}
		}
	}

	return ResultData;
}
