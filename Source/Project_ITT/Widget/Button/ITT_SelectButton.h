// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Button.h"
#include "ITT_SelectButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_SelectButton : public UITT_Button
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void SetButtonData(const FString& ButtonName) const;
	
private:
	UPROPERTY(Category= UITT_DefaultButton, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString ButtonText = "Blank Text";
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ButtonName = nullptr;
};
