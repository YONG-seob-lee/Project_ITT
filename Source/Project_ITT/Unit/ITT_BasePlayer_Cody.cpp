// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer_Cody.h"

#include "ITT_BasePlayer_Nail.h"
#include "ITT_InstUtil.h"
#include "ITT_PlayerController.h"
#include "Camera/ITT_Actor_Camera.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ITT_CameraManager.h"
#include "Manager/ITT_InputManager.h"
#include "Manager/ITT_UnitManager.h"
#include "Manager/ITT_WidgetManager.h"
#include "Manager/Tool/WidgetTool/ITT_BuiltInWidgetTool.h"
#include "Widget/Aim/ITT_Widget_Aimed.h"

namespace SocketName
{
	const FName Nail_0 = TEXT("NailSocket_0");
	const FName Nail_1 = TEXT("NailSocket_1"); 
	const FName Nail_2 = TEXT("NailSocket_2");
	const FName NailCatchSocket = TEXT("NailCatchSocket");
}

void UITT_BasePlayer_Cody::Initialize()
{
	Super::Initialize();
	
	gInputMng.GetBindAimedDelegate().AddUObject(this, &UITT_BasePlayer_Cody::SetAimed);
	gInputMng.GetBindFireDelegate().AddUObject(this, &UITT_BasePlayer_Cody::ThrowNail);
	AimWidget = gWidgetMng.GetBuiltInWidgetTool()->GetAimWidget();
}

void UITT_BasePlayer_Cody::PostInitialize()
{
	Super::PostInitialize();

	CodyCharacterBase = GetCharacterBase();
	if(CodyCharacterBase.IsValid() == false)
	{
		return;
	}
	
	MakeNail(1, SocketName::Nail_0);
	MakeNail(2, SocketName::Nail_1);
	MakeNail(3, SocketName::Nail_2);
}

void UITT_BasePlayer_Cody::Finalize()
{
	if(Cody_CameraCapsuleComponent.IsValid())
	{
		Cody_CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	const TObjectPtr<AITT_PlayerController> PlayerController = Cast<AITT_PlayerController>(UITT_InstUtil::GetPlayerController());
	if(PlayerController == nullptr)
	{
		return;
	}
	
	if(const TObjectPtr<UITT_UnitBase> UnitBase = gUnitMng.GetUnit(PlayerController->GetUnitHandle()))
	{
		UnitBase->OnActorTickDelegate.Remove(ActorTickEvent);
	}

	PlayerController->ResetUnitHandle();
	ActorTickEvent.Reset();
	
	gInputMng.GetBindAimedDelegate().RemoveAll(this);
	Super::Finalize();
}

void UITT_BasePlayer_Cody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bAimed)
	{
		NailTrace();
	}
}

void UITT_BasePlayer_Cody::InitCamera()
{
	Aim_Camera = gCameraMng.CreateCameraActor(AITT_Actor_Camera::StaticClass(), EITT_GameCameraType::Practice);

	if(Aim_Camera == nullptr)
	{
		ITT_LOG(TEXT("No camera object created. Check out the camera manager."))
		return;
	}
	
	Aim_Camera->InitialInput(TEXT("Practice_AimCamera"));
	
	// 일단 코디 카메라만 만들어두고 나중에 메이가 필요할 때 추가.
	Cody_Camera = gCameraMng.CreateCameraActor(AITT_Actor_Camera::StaticClass(), EITT_GameCameraType::Practice);

	if(Cody_Camera == nullptr)
	{
		ITT_LOG(TEXT("No camera object created. Check out the camera manager."))
		return;
	}
	
	Cody_Camera->InitialInput(TEXT("Practice_CodyCamera"));
	TArray<UActorComponent*> CapsuleComponents = Cody_Camera->GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("CameraCollision"));
	if(CapsuleComponents.Num() > 0)
	{
		Cody_CameraCapsuleComponent = Cast<UCapsuleComponent>(CapsuleComponents[0]);

		if(Cody_CameraCapsuleComponent.IsValid())
		{
			Cody_CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		}
	}
	
	ActorTickEvent = OnActorTickDelegate.AddUObject(this, &UITT_BasePlayer_Cody::ActorTickFunc);
	
	// Step 02. 해당 카메라 활성화
	gCameraMng.ActiveCamera(Cody_Camera);
}

void UITT_BasePlayer_Cody::MakeNail(int32 HolsterIndex, FName SocketName)
{
	USkeletalMeshComponent* CodyMesh = CodyCharacterBase->GetMesh();
	if(!CodyMesh)
	{
		return;
	}
	
	if(CodyMesh->DoesSocketExist(SocketName))
	{
		const TObjectPtr<UITT_BasePlayer_Nail> Nail = Cast<UITT_BasePlayer_Nail>(gUnitMng.CreateUnit(static_cast<int32>(ITT_Character::Nail), UITT_BasePlayer_Nail::StaticClass()));
		if(!Nail)
		{
			return;
		}

		//Nail 위치 조정
		Nail->AttachNail(CodyMesh, SocketName);

		HolsterSocket.Emplace(HolsterIndex, SocketName);
		HolsterNails.Emplace(HolsterIndex, Nail);
	}
}

void UITT_BasePlayer_Cody::SetAimed()
{
	if(bAimed == false)
	{
		if(AimWidget)
		{
			AimWidget->AddToViewport(10000);
			AimWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		
		// Step1. Camera Change
	    gCameraMng.ActiveCamera(Aim_Camera, 0.2f);
		
		// Step2. Nail Attach
		AttachHand();
		bAimed = true;
	}
	else
	{
		if(AimWidget)
		{
			AimWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		gCameraMng.ActiveCamera(Cody_Camera, 0.2f);
		AttachHand(false);
		bAimed = false;
	}
}

void UITT_BasePlayer_Cody::ThrowNail()
{
	TargetNail->DetachNail();
	TargetNail->Fire(ShootDirection);
}

void UITT_BasePlayer_Cody::AttachHand(bool bAttachHand /* = true */)
{
	const int32 TargetIndex = GetTargetNail(bAttachHand == false);
	
	USkeletalMeshComponent* CodyMesh = CodyCharacterBase->GetMesh();
	if(!CodyMesh)
	{
		return;
	}

	
	if(bAttachHand)
	{
		TargetNail = *HolsterNails.Find(TargetIndex);
		if(TargetNail)
		{
			TargetNail->AttachNail(CodyMesh, SocketName::NailCatchSocket);
			//TargetNail->SetRotator(FRotator(-90.f, 0.f, 30.f));
			HolsterNails.Emplace(TargetIndex, nullptr);
		}
	}
	else
	{
		const FName* SocketName = HolsterSocket.Find(TargetIndex);
		if(!SocketName)
		{
			return;
		}
		if(TargetNail)
		{
			TargetNail->AttachNail(CodyMesh, *SocketName);
			//TargetNail->SetRotator(FRotator(0.f, 0.f, 0.f));
			
			HolsterNails.Emplace(TargetIndex, TargetNail);
			TargetNail = nullptr;
		}
	}
}

int32 UITT_BasePlayer_Cody::GetTargetNail(bool bFindEmpty)
{
	for(const auto & Nail : HolsterNails)
	{
		if(bFindEmpty)
		{
			if(Nail.Value == nullptr)
			{
				return Nail.Key;
			}
		}
		else
		{
			if(Nail.Value != nullptr)
			{
				return Nail.Key;
			}	
		}
	}

	return 0;
}

void UITT_BasePlayer_Cody::ActorTickFunc(TObjectPtr<UITT_UnitBase> Unit)
{
	if(Unit == nullptr)
	{
		return;
	}

	const TObjectPtr<AITT_CharacterBase> Character = Unit->GetCharacterBase();

	if(Character == nullptr)
	{
		return;
	}

	if(bAimed == false)
	{
		Cody_Camera->SetCameraAspectRatio(UITT_InstUtil::GetAspectRatio());
		Cody_Camera->SetFieldOfView(80.f);
		Cody_Camera->SetSpringOffset(FVector(0.f, 0.f, 140.f));
		Cody_Camera->SetCameraDistance(FVector(0.f, 0.f, 140.f).Size());
		Cody_Camera->SetTargetRotator(FRotator(0.f, 0.f, 0.f));

		// Camera Step - 카메라의 위치 "UnitVector" 은 계속 따라다녀야하는데, 유닛의 방향은 알 필요가 없다. 하지만 최초 캐릭터와 카메라는 같은 방향을 바라보아야하기 때문에 딱 한번 맞춰주어야함
		Cody_Camera->SetTargetPosition(Character->GetCurrentLocation());
	}
	else
	{
		Aim_Camera->SetCameraAspectRatio(UITT_InstUtil::GetAspectRatio());
		Aim_Camera->SetFieldOfView(80.f);
		Cody_Camera->SetSpringOffset(FVector(0.f, 0.f, 140.f));
		Cody_Camera->SetCameraDistance(FVector(0.f, 0.f, 140.f).Size());
		Aim_Camera->SetCameraRelativeLocation(FVector(-300.f, 100.f, 50.f));
		Aim_Camera->SetCameraRelativeRotation(FRotator(0.f, 0.f, 0.f));
		Aim_Camera->SetTargetRotator(FRotator(0.f, 0.f, 0.f));
		
		Aim_Camera->SetTargetPosition(Character->GetCurrentLocation());

		if(CodyCharacterBase.IsValid())
		{
			CodyCharacterBase->SetAimMode(true);
		}
	}
}

void UITT_BasePlayer_Cody::NailTrace()
{
	const TObjectPtr<APlayerController> Controller = UITT_InstUtil::GetPlayerController();
	if(!Controller)
	{
		return;
	}
	constexpr float NailThrowDistance = 10000.f;
	FVector NailStartPoint;

	//const FVector ActorLocation = -CodyCharacterBase->GetActorRightVector();
	//ITT_LOG(TEXT("%s"), *ActorLocation.ToString());
	
	
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize( ViewportSize );
	UGameplayStatics::DeprojectScreenToWorld(Controller, ViewportSize / 2,  NailStartPoint, ShootDirection);
	
	const FVector NailEndPoint = NailStartPoint + ShootDirection * NailThrowDistance;

	FHitResult HitResult;
	const TArray<AActor*> IgnoreActor;
	UKismetSystemLibrary::LineTraceSingle(UITT_InstUtil::GetGameWorld(), NailStartPoint, NailEndPoint, TraceTypeQuery1, false, IgnoreActor, EDrawDebugTrace::ForDuration, HitResult, true);
}
