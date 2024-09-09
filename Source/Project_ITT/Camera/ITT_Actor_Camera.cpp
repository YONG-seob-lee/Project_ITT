// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Actor_Camera.h"

#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Manager/ITT_InputManager.h"

AITT_Actor_Camera::AITT_Actor_Camera()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	if(SceneComponent)
	{
		RootComponent = SceneComponent;
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if(SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(RootComponent);
		SpringArmComponent->bEnableCameraLag = false;
		SpringArmComponent->bEnableCameraRotationLag = false;
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = true;
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if(CameraComponent)
	{
		CameraComponent->FieldOfView = 90.f;
		CameraComponent->bConstrainAspectRatio = true;
		CameraComponent->AspectRatio = 1.777778f;
		CameraComponent->PostProcessBlendWeight = 1.f;
		CameraComponent->SetRelativeRotation(FRotator(-23.f, 0.f, 0.f));
		CameraComponent->SetRelativeLocation(FVector(-500.f, 0.f, 0.f));
		CameraComponent->SetupAttachment(SpringArmComponent);
	}
}

void AITT_Actor_Camera::SetAspectRatio(float AspectRatio) const
{
	if(CameraComponent)
	{
		CameraComponent->SetAspectRatio(AspectRatio);
	}
}

void AITT_Actor_Camera::SetTargetPosition(const FVector& TargetPosition)
{
	SetActorLocation(TargetPosition);
}

void AITT_Actor_Camera::SetTargetRotator(const FRotator& TargetRotator)
{
	SetActorRotation(TargetRotator);

	FirstCameraRotator = GetActorRotation();
}

void AITT_Actor_Camera::RotateCamera()
{
	// FRotator( Pitch : 고개 위아래, Yaw : 고개 좌우, Roll : 이건 무조건 0)
	CachedMovedCameraRotator += FRotator(CameraJoyStickDistance.Y, CameraJoyStickDistance.X, 0.f);
	SetActorRotation(FirstCameraRotator + CachedMovedCameraRotator);
	
	//SpringArmComponent->AddRelativeRotation(FRotator(CameraJoyStickDistance.Y, CameraJoyStickDistance.X, 0.f));
}

void AITT_Actor_Camera::SetRotateNative()
{
	if(CameraComponent)
	{
		CameraComponent->SetRelativeRotation(FRotator(-20.f, -90.f, 0.f));
	}
}

void AITT_Actor_Camera::SetCameraRelativeLocation(const FVector& Location) const
{
	if(CameraComponent)
	{
		CameraComponent->SetRelativeLocation(Location);
	}
}

void AITT_Actor_Camera::SetCameraRelativeRotation(const FRotator& Rotator) const
{
	if(CameraComponent)
	{
		CameraComponent->SetRelativeRotation(Rotator);
	}
}

void AITT_Actor_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

void AITT_Actor_Camera::RegistAxis()
{
	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &AITT_Actor_Camera::OnAxisUpDown);
	gInputMng.RegistAxis(EITT_Axis_Type::Right, EITT_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &AITT_Actor_Camera::OnAxisLeftRight);
	gInputMng.RegistAxis(EITT_Axis_Type::Right, EITT_Action_Type::ActionLeftRight, LeftRightDelegate);
}

void AITT_Actor_Camera::CameraMoveProcess()
{
	if(CameraJoyStickDistance.Size() > 0.01f)
	{
		RotateCamera();
	}

	CameraJoyStickDistance.X = CameraJoyStickDistance.Y = 0.f;
}

void AITT_Actor_Camera::OnAxisUpDown(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		CameraJoyStickDistance.Y = Value;
	}
}

void AITT_Actor_Camera::OnAxisLeftRight(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		CameraJoyStickDistance.X = Value;
	}
}

void AITT_Actor_Camera::InitialInput(const FString& _CameraName)
{
	CameraName = _CameraName;
	SetActorLabel(_CameraName);

	RegistAxis();
}

bool AITT_Actor_Camera::Create(const FString& _CameraName, const FVector& Position, const FVector& TargetPosition,
	float Fov, float AspectRatio, bool bPerspective)
{
	CameraName = _CameraName;
#if WITH_EDITOR
	SetActorLabel(_CameraName);
#endif

	//SetTargetPosition(TargetPosition);
	SetFieldOfView(Fov);
	SetAspectRatio(AspectRatio);

	bPerspective ? CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective) : CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	//CreatePostEffectMaterial();
	
	return true;
}

void AITT_Actor_Camera::Destroy()
{
}

void AITT_Actor_Camera::PreProcess(float DeltaSeconds)
{
}

void AITT_Actor_Camera::Active(float BlendTime)
{
	const TObjectPtr<APlayerController> PlayerController = UITT_InstUtil::GetPlayerController();
	if(PlayerController == nullptr)
	{
		return;
	}
	
	if(PlayerController->GetViewTarget() != this)
	{
		BlendTime > 0.f ? PlayerController->SetViewTargetWithBlend(this, BlendTime) : PlayerController->SetViewTarget(this);
	}
}

// Called every frame
void AITT_Actor_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

