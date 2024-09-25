// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ITT_TitleDefine.h"
#include "ITT_Define.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(My_Log, Log, All);

#define ITT_LOG(InFormat, ...) UE_LOG(My_Log, Log, InFormat, ##__VA_ARGS__)
#define ITT_LOG_Verbosity(verbosity, msg, ...) UE_LOG(My_Log, verbosity, msg, ##__VA_ARGS__)

#define ITT_CHECK(expr) check(expr)

#define ITT_NewObject NewObject
#define ITT_DeleteObject(Object) {										\
									ITT_CHECK(Object != nullptr);					\
									Object->ConditionalBeginDestroy();	\
								 };

/////////////////////////
///
///			Scene Part



UENUM(BlueprintType)
enum class EITT_GameSceneType : uint8
{
	None = 0	UMETA(DisplayName = "None"),

	Logo		UMETA(DisplayName = "Logo"),
	Title		UMETA(DisplayName = "Title"),
	Chapter_01	UMETA(DisplayName = "Chapter_01"),
	Chapter_02	UMETA(DisplayName = "Chapter_02"),
	Practice	UMETA(DisplayName = "Practice"),
};

namespace LevelPath
{
	const FString Logo = TEXT("/Game/Maps/Chapter_0/Logo");
	const FString Title = TEXT("/Game/Maps/Chapter_0/Title");
	const FString Chapter_1 = TEXT("/Game/Maps/Chapter_1/Chapter_1");
	const FString Chapter_2 = TEXT("/Game/Maps/Chapter_1/Chapter_2");
	const FString Practice = TEXT("/Game/Maps/Practice_Level");
}


enum class EITT_ChangeSceneStep
{
	Ready = 0,
	StartLoadLevel,
	PrepareSceneState,
	Complete,
};

DECLARE_DELEGATE_OneParam(FITT_LoadLevelInitialized, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FITT_ChangeSceneDelegate, EITT_GameSceneType);
DECLARE_MULTICAST_DELEGATE_OneParam(FITT_LoadLevelDelegate, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FITT_ChangeSceneState, uint8);

USTRUCT()
struct FITT_ChangeSceneData
{
	GENERATED_USTRUCT_BODY();
	
	EITT_GameSceneType SceneType;
	EITT_ChangeSceneStep Step;
	FName LevelPackagePath;
};



/////////////////////////
///
///			Fade(Scene) Part

enum class EITT_FadeStep
{
	Ready = 0,
	EnterFadeOut,
	ExitFadeOut,
	EnterFadeIn,
	ExitFadeIn,
};

enum class EITT_FadeStyle
{
	None = 0,
	Dialog,
};

enum class EITT_LoadingPageType
{
	None = 0,
	EnterFirst,
	ShowWorldMap,
};

DECLARE_DELEGATE(FITT_FadeEventDelegate);
DECLARE_DELEGATE_RetVal(bool, FITT_FadeCheckLoadDelegate);


/////////////////////////
///
///			Table Part

DECLARE_DELEGATE_TwoParams(FITT_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class EITT_TableDataType : uint8
{
	Common = 0						UMETA(DisplayName = "Common"),
	Resource_Widget					UMETA(DisplayName = "Resource_Widget"),
	Resource_Unit					UMETA(DisplayName = "Resource_Unit"),

	BasePath_Directory				UMETA(DisplayName = "BasePath_Directory"),
	BasePath_BP_File				UMETA(DisplayName = "BasePath_BP_File"),
	BasePath_Img_File				UMETA(DisplayName = "BasePath_Img_File"),

	SelectButton					UMETA(DisplayName = "SelectButton"),
	
	PlayerStatus					UMETA(DisplayName = "PlayerStatus"),
	Enemy							UMETA(DisplayName = "Enemy"),
};

USTRUCT()
struct FITT_TableMapperData
{
	GENERATED_USTRUCT_BODY()
public:
	FITT_TableMapperData() {}
	
	FITT_TableMapperData(const FString& _TablePath, const TObjectPtr<UDataTable>& _TableData, const TObjectPtr<class UITT_TableMapper>& _TableMapper) 
							: TablePath(_TablePath), TableData(_TableData), TableMapper(_TableMapper) {}
	~FITT_TableMapperData() { TableData = nullptr; TableMapper = nullptr; }

	void Finalize();
	
	FORCEINLINE const FString& GetTablePath() { return TablePath; }
	FORCEINLINE TObjectPtr<UDataTable> GetTableData() const { return TableData; }
	FORCEINLINE TObjectPtr<UITT_TableMapper> GetTableMapper() const { return TableMapper; }
private:
	FString TablePath = FString();
	
	UPROPERTY()
	TObjectPtr<UDataTable> TableData = nullptr;
	UPROPERTY()
	TObjectPtr<UITT_TableMapper> TableMapper = nullptr;
};


/////////////////////////
///
///			Widget Part

UENUM(BlueprintType)
enum class EITT_ExclusiveGroup : uint8
{
	InVaild = 0,
	ContentMenu = 1,
	ContentSubMenu1 = 2,
	ContentSubMenu2 = 3,
	ContentSubMenu3 = 4,
	ContentSubMenu4 = 5,
	ContentSubMenu5 = 6,
	ContentSubMenu6 = 7,
	ContentSubMenu7 = 8,
	ContentSubMenu8 = 9,
	ContentSubMenu9 = 10,
	ContentSubMenu10 = 11,
	ContentSubMenu11 = 12,
	ContentSubMenu12 = 13,
	ContentSubMenu13 = 14,
	ContentSubMenu14 = 15,
	ContentSubMenu15 = 16,
	ContentSubMenu16 = 17,
	ContentSubMenu17 = 18,
	ContentSubMenu18 = 19,
	ContentSubMenu19 = 20,
	ContentSubMenu20 = 21,
	ContentSubMenu21 = 22,
	ContentSubMenu22 = 23,
	ContentSubMenu23 = 24,
	ContentSubMenu24 = 25,
	ContentSubMenu25 = 26,
	ContentSubMenu26 = 27,
	TopMenu = 28,
	Max
};

struct FITT_ResourceWidgetInfo
{
	FITT_ResourceWidgetInfo(): zOrder(0), ExclusiveGroup(), NotRender3D(false), bNotClosing(false), CreateTime(0) {}

	FString File;
	FName TypeName;
	int32 zOrder;
	EITT_ExclusiveGroup ExclusiveGroup;
	bool NotRender3D;
	bool bNotClosing;
	float CreateTime;
	
	FORCEINLINE const FName& GetWidgetName() const { return TypeName; }
	FORCEINLINE const EITT_ExclusiveGroup& GetExclusiveGroup() const { return ExclusiveGroup; }
};

DECLARE_MULTICAST_DELEGATE_OneParam(FITT_CreateWidget, const FName&);
DECLARE_MULTICAST_DELEGATE_OneParam(FITT_DestroyWidget, const FName&);

/////////////////////////
///
///			Camera Part

UENUM(BlueprintType)
enum class EITT_GameCameraType : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	
	Title		UMETA(DisplayName = "Title"),
	Chapter_01	UMETA(DisplayName = "Chapter_01"),
	Chapter_02	UMETA(DisplayName = "Chapter_02"),
	Practice	UMETA(DisplayName = "Practice"),
};


/////////////////////////
///
///			Input Part



UENUM(BlueprintType)
enum class EITT_Axis_Type : uint8
{
	Left	UMETA(DisplayName = "Axis_Type_Left"),
	Right	UMETA(DisplayName = "Axis_Type_Right"),
	Pinch	UMETA(DisplayName = "Axis_Type_Pinch"),
};

UENUM(BlueprintType)
enum class EITT_Action_Type : uint8
{
	ActionUpDown		UMETA(DisplayName = "Action_Type_UpDown"),
	ActionLeftRight		UMETA(DisplayName = "Action_Type_LeftRight"),
	Interaction			UMETA(DiaplayName = "Interaction"),
};

UENUM(BlueprintType)
enum class EITT_Touch_Event : uint8
{
	Down	UMETA(DisplayName = "Touch_Event_Down"),
	Up		UMETA(DisplayName = "Touch_Event_Up"),
	Move	UMETA(DisplayName = "Touch_Event_Move"),
};

UENUM(BlueprintType)
enum class EITT_AndroidButton_Type : uint8
{
	Back	UMETA(DisplayName = "AndroidButton_Back"),
	Menu	UMETA(DisplayName = "AndroidButton_Menu"),
};

DECLARE_DELEGATE_TwoParams(FBindAllKeysDelegate, const FKey&, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindSelectDelegate, ITT_Player, float);
DECLARE_MULTICAST_DELEGATE(FBindPickDelegate);
DECLARE_MULTICAST_DELEGATE(FBindAimedDelegate);
DECLARE_MULTICAST_DELEGATE(FBindFireDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FBindScreenMoveDelegate, FVector2D);
DECLARE_MULTICAST_DELEGATE(FBindScreenSplitTypeDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FBindMoveButtonDelegate, bool);
DECLARE_MULTICAST_DELEGATE(FBindSelectButtonDelegate);
/////////////////////////
///
///			Unit Part

typedef int32 ITT_Handle;
constexpr int32 InvalidUnitHandle = 0;

UENUM()
enum class ITT_Character : int32
{
	None = 0			UMETA(DisplayName = "None"),
	Cody = 1			UMETA(DisplayName = "Cody"),
	May = 2				UMETA(DisplayName = "May"),
	Rose = 3			UMETA(DisplayName = "Rose"),
	CodyDoll = 4		UMETA(DisplayName = "CodyDoll"),
	MayDoll = 5			UMETA(DisplayName = "MayDoll"),
	Dummy = 6			UMETA(DisplayName = "Dummy"),
	Nail = 7			UMETA(DisplayName = "Nail"),
};


UENUM()
enum class EITT_UnitState : uint32
{
	None = 0,
	Title,
	Chapter_01,
	Chapter_02,
	Practice,
};

UENUM(BlueprintType)
enum class EITT_UnitActionState : uint8
{
	None = 0					UMETA(DisplayName = "None"),
	Player_Normal				UMETA(DisplayName = "Player_Normal"),
	Select_PickMove				UMETA(DisplayName = "Select_Character"),
	Select_Pick					UMETA(DisplayName = "Select_Pick"),
};

USTRUCT(BlueprintType)
struct FITT_CharacterLodValues
{
	GENERATED_BODY()
	FITT_CharacterLodValues() {}

public:
	UPROPERTY(Category = "FITT_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CullDistance = 0;

	UPROPERTY(Category = "FITT_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 OutLineCullDistance = 0;

	// not used
	UPROPERTY(Category = "FITT_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) 
	int32 AnimMaxDistanceFactor = 0;

	UPROPERTY(Category = "FITT_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<float> AnimThresholdTable;

	UPROPERTY(Category = "FITT_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 BaseNonRenderedUpdateRate = 0;

	float CullDistanceScale = 1.0f;
	float OutLineCullDistanceScale = 1.0f;
	bool  bVisibleOutLine = true;
};

/////////////////////////
///
///			Animation
USTRUCT(Blueprintable)
struct FITT_AnimSequence
{
	GENERATED_BODY()

	FITT_AnimSequence()
		: Probability(0.f)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAnimSequenceBase> ObjectPtr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Probability;
};

USTRUCT(Blueprintable)
struct FITT_AnimSequenceData
{
	GENERATED_BODY()

	FITT_AnimSequenceData()
		: bLoop(false)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_AnimSequence AnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoop;
};

USTRUCT(Blueprintable)
struct FITT_AnimSequencesData
{
	GENERATED_BODY()

	FITT_AnimSequencesData()
		: bPickHighestProbabilityOnInit(true), bPickHighestProabilityAfterLowProbability(true), bLoop(true)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FITT_AnimSequence> AnimSequences;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPickHighestProbabilityOnInit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPickHighestProabilityAfterLowProbability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoop;
};

USTRUCT(Blueprintable)
struct FITT_BlendSpace
{
	GENERATED_BODY()

	FITT_BlendSpace()
		: Probability(0.f)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBlendSpace> ObjectPtr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Probability;
};

USTRUCT(Blueprintable)
struct FITT_BlendSpaceData
{
	GENERATED_BODY()

	FITT_BlendSpaceData()
		: bInitializeToCurrentInputValues(false), bLoop(true)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITT_BlendSpace BlendSpace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInitializeToCurrentInputValues;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoop;
};

UENUM(BlueprintType)
enum class EITT_CharacterState : uint8
{
	Deactive,
	Movement,
	Sprint,
	Jump,
	DoubleJump,
	Landing,
	Dash,
	Crouch,
	Roll,
	Aim,
	Throw,
	Fire,
	
	// RosePart
	Select,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FITT_UnitActorTickDelegate, TObjectPtr<class UITT_UnitBase>);