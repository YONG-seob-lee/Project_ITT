// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_ITT/ITT_Define.h"
#include "ITT_Widget.generated.h"

namespace DefaultWidgetAnimation
{
	const FName Appearance = TEXT("Appearance");
	const FName DisAppearance = TEXT("DisAppearance");
	
	const FName Idle = TEXT("Idle");
}

/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE FITT_ResourceWidgetInfo GetResourceWidgetInfo() const { return ResourceWidgetInfo; }
	FORCEINLINE void SetResourceWidgetInfo(const FITT_ResourceWidgetInfo& Info) { ResourceWidgetInfo = Info; }
	FORCEINLINE void SetZOrder(int32 _ZOrder) { ZOrder = _ZOrder; }
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate = true);
	virtual void FinishWidget();

	virtual void SynchronizeProperties() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void Active(bool _bActive = true);
	
	virtual void OnAnimationStarted_Implementation(const UWidgetAnimation* Animation) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	void Init();
	
	void PlayAnimationByName(FName Name, float StartTime = 0.f, int32 LoopCount = 1, EUMGSequencePlayMode::Type PlayType = EUMGSequencePlayMode::Forward, float Speed = 1.f);
	TObjectPtr<UWidgetAnimation> GetAnimationByName(FName AnimName) const;
	bool StopAnimation(const FName& AnimName);
	
	bool IsExistAnim(FName AnimName) const;

	void FillDefaultAnimations();
protected:
	void InitResourceWidgetInfo();
	
	virtual void OnAnimFinished(const FName& AnimName);
	
	bool bManaged = false;
	bool bActive = false;
	bool bAddToViewport = false;
	
	UPROPERTY(Category = UITT_Widget, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ZOrder = 0;
	
	UPROPERTY()
	TMap<FName, TObjectPtr<UWidgetAnimation>> Animations;
	
	FITT_ResourceWidgetInfo ResourceWidgetInfo;

private:
	
};
