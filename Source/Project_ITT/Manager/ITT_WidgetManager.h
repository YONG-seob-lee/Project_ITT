// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITT_Singleton.h"
#include "UObject/Object.h"
#include "ITT_WidgetManager.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_ITT_API UITT_WidgetManager : public UObject, public UITT_Singleton<UITT_WidgetManager>
{
	GENERATED_BODY()
public:

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float DeltaTime) override;
	
	TObjectPtr<class UITT_Widget> GetWidget(const FName& TypeName);
	TObjectPtr<class UITT_Widget> Create_Widget(const FName& TypeName);
	TObjectPtr<class UITT_Widget> Create_Widget_NotManaging(const FSoftObjectPath& SoftObjectPath);

	void PreDestroyWidget(TObjectPtr<class UITT_Widget> Widget);
	bool DestroyWidget(const FName& TypeName);
	void PostDestroyWidget(const FName& TypeName);

	void ClearExclusiveLayer();

	void Test(UITT_Widget* Widget);
	
	FITT_CreateWidget OnCreateWidget;
	FITT_DestroyWidget OnDestroyWidget;

	TObjectPtr<class UITT_BuiltInWidgetTool> GetBuiltInWidgetTool() const { return BuiltInTool; }
	
private:
	TObjectPtr<class UITT_Widget> CreateWidget_Internal(const FName& TypeName, bool bManaged);
	TObjectPtr<class UITT_Widget> CreateWidget_Internal_Managing(const FString& Path);
	TObjectPtr<class UITT_Widget> CreateWidget_Internal_NotManaging(const FString& Path) const;

	
	void AddExclusiveLayerWidget(TObjectPtr<class UITT_Widget> Widget);
	void RemoveExclusiveLayerWidget(TObjectPtr<class UITT_Widget> Widget);

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData);
	
	UPROPERTY()
	TArray<TObjectPtr<class UITT_Widget>> ExclusiveLayers;
	
	UPROPERTY()
	TMap<FName, TWeakObjectPtr<class UITT_Widget>> ManagedWidgets;

	UPROPERTY()
	TObjectPtr<UITT_BuiltInWidgetTool> BuiltInTool = nullptr;
	
#define	gWidgetMng (*UITT_WidgetManager::GetInstance())
};
