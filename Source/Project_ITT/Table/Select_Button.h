#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Select_Button.generated.h"
    
USTRUCT()
struct FSelectButton : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
    int32 Index = 0;
	UPROPERTY(EditAnywhere)
    FString ButtonName = FString();
	UPROPERTY(EditAnywhere)
	int32 SceneType = 0;
	UPROPERTY(EditAnywhere)
	FString LevelPath = FString();
};
