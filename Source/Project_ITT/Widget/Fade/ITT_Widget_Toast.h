// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_ITT/Widget/ITT_Widget.h"
#include "ITT_Widget_Toast.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget_Toast : public UITT_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/Widgets/Fade/Toast_Widget.Toast_Widget")); }
};
