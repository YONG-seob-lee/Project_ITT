// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "UObject/Object.h"
#include "ITT_FadeCommand.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_FadeCommand : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetFadeStyle(EITT_FadeStyle FadeStyle) { Fade = FadeStyle; }
	FORCEINLINE void SetIsDirectFadeOut(bool _bDirectFadeOut) { bDirectFadeOut = _bDirectFadeOut; }
	FORCEINLINE void SetLoadingPageType(EITT_LoadingPageType Type) { LoadingPageType = Type; }
	
	FORCEINLINE EITT_FadeStyle GetFadeType() const { return Fade; }
	FORCEINLINE bool GetIsDirectFadeOut() const { return bDirectFadeOut; }
	FORCEINLINE EITT_LoadingPageType GetLoadingPageType() const { return LoadingPageType; }
	
	FITT_FadeEventDelegate OnFadeOutComplete;
	FITT_FadeEventDelegate OnFadeInStart;
	FITT_FadeEventDelegate OnFadeInComplete;

	FITT_FadeCheckLoadDelegate OnCheckLoadComplete;
	
	void SetCreateFrom(const ANSICHAR* File, const int32 Line);
private:
	EITT_FadeStyle Fade = EITT_FadeStyle::None;
	EITT_LoadingPageType LoadingPageType = EITT_LoadingPageType::None;
	bool bDirectFadeOut = false;
	
	FString CreateFileLine = FString();
};
