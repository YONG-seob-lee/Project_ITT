// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_InputManager.h"

#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/Pawn/ITT_Pawn_Input.h"

void UITT_InputManager::Initialize()
{
	IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UITT_InputManager::OnControllerConnectionChange);
	IPlatformInputDeviceMapper::Get().GetOnInputDevicePairingChange().AddUObject(this, &UITT_InputManager::OnControllerPairingChange);
	
}

void UITT_InputManager::PostInitialize()
{
	if(const TObjectPtr<APlayerController> Controller = UITT_InstUtil::GetPlayerController())
	{
		const ULocalPlayer* LocalPlayer = Controller->GetLocalPlayer();
		if(UCommonInputSubsystem* Input = LocalPlayer->GetSubsystem<UCommonInputSubsystem>())
		{
			Input->OnInputMethodChangedNative.AddUObject(this, &UITT_InputManager::OnInputMethodChanged);
		}	
	}
}

void UITT_InputManager::Finalize()
{
	UITT_Singleton<UITT_InputManager>::Finalize();
}

void UITT_InputManager::Tick(float _DeltaTime)
{
	UITT_Singleton<UITT_InputManager>::Tick(_DeltaTime);
}

void UITT_InputManager::RegistAxis(EITT_Axis_Type AxisType, EITT_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event)
{
	if(AxisType == EITT_Axis_Type::Left)
	{
		if(ActionType == EITT_Action_Type::ActionUpDown)
		{
			CharacterMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == EITT_Action_Type::ActionLeftRight)
		{
			CharacterMove_LeftRightEvent.AxisDelegate = Event;
		}	
	}
	else if(AxisType == EITT_Axis_Type::Right)
	{
		if(ActionType == EITT_Action_Type::ActionUpDown)
		{
			CameraMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == EITT_Action_Type::ActionLeftRight)
		{
			CameraMove_LeftRightEvent.AxisDelegate = Event;
		}
	}
}

void UITT_InputManager::RegistAxis_Select(EITT_Axis_Type AxisType, EITT_Action_Type ActionType,
	const FInputAxisUnifiedDelegate& Event)
{
	if(ActionType != EITT_Action_Type::ActionLeftRight)
	{
		return;
	}

	SelectMove_Event.AxisDelegate = Event;
}

void UITT_InputManager::RegistTouch(EITT_Touch_Event TouchEventType, const FInputTouchBinding& Event)
{
	if(TouchEventType == EITT_Touch_Event::Down)
	{
		TouchDownEvent = Event;
	}
	else if(TouchEventType == EITT_Touch_Event::Up)
	{
		TouchUpEvent = Event;
	}
	else if(TouchEventType == EITT_Touch_Event::Move)
	{
		TouchMoveEvent = Event;
	}
}

void UITT_InputManager::RegistAndroidButton(EITT_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate)
{
	if(ButtonType == EITT_AndroidButton_Type::Back)
	{
		AndroidBackDelegate = Delegate;
	}
	else if(ButtonType == EITT_AndroidButton_Type::Menu)
	{
		AndroidMenuDelegate = Delegate;
	}
}

void UITT_InputManager::RegistInteractionButton(const FSimpleDelegate& Delegate)
{
	InteractionDelegate = Delegate;
}

void UITT_InputManager::RegistSelectCharacterButton(const FSimpleDelegate& Delegate)
{
	SelectCharacterButton = Delegate;
}

void UITT_InputManager::CreateInputPawn()
{
	if(InputPawn != nullptr)
	{
		return;
	}

	InputPawn = Cast<AITT_Pawn_Input>(UITT_InstUtil::SpawnActor(AITT_Pawn_Input::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, TEXT("InputPawn"), ESpawnActorCollisionHandlingMethod::AlwaysSpawn, true));
	if(InputPawn)
	{
		InputPawn->Create();
	}
}

void UITT_InputManager::DestroyInputPawn()
{
	if(InputPawn != nullptr)
	{
		InputPawn->Destroy();

		if(InputPawn->IsRooted())
		{
			InputPawn->RemoveFromRoot();
		}

		UITT_InstUtil::GetGameWorld()->DestroyActor(InputPawn);
		
		InputPawn = nullptr;
	}
}

void UITT_InputManager::LeftAxisUpDown(float Value)
{
	CharacterMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UITT_InputManager::LeftAxisLeftRight(float Value)
{
	CharacterMove_LeftRightEvent.AxisDelegate.Execute(Value);
}

void UITT_InputManager::RightAxisUpDown(float Value)
{
	CameraMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UITT_InputManager::RightAxisLeftRight(float Value)
{
	CameraMove_LeftRightEvent.AxisDelegate.Execute(Value);
}

void UITT_InputManager::LeftAxis_Select(float Value)
{
	SelectMove_Event.AxisDelegate.Execute(Value);
}


void UITT_InputManager::OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchDownEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UITT_InputManager::OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchUpEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UITT_InputManager::OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchMoveEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UITT_InputManager::AndroidBack()
{
	if(AndroidBackDelegate.IsBound())
	{
		AndroidBackDelegate.Execute();
	}
}

void UITT_InputManager::AndroidMenu()
{
	if(AndroidMenuDelegate.IsBound())
	{
		AndroidMenuDelegate.Execute();
	}
}

void UITT_InputManager::Interaction()
{
	if(InteractionDelegate.IsBound())
	{
		InteractionDelegate.Execute();
	}
}

void UITT_InputManager::OnControllerConnectionChange(EInputDeviceConnectionState InputDeviceConnectionState,
	FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId)
{
	const FString ConnectionState = UITT_InstUtil::ConvertEnumToString("EInputDeviceConnectionState", InputDeviceConnectionState);
	ITT_LOG(TEXT("UITT_InstUtil::OnControllerConnectionChange  CommonInput : %s"), *ConnectionState);

	OnControllerConnectionChangedDelegate.Broadcast(InputDeviceConnectionState);
}

void UITT_InputManager::OnControllerPairingChange(FInputDeviceId InputDeviceId, FPlatformUserId PlatformUserId,
	FPlatformUserId PlatformUserId1)
{
}

void UITT_InputManager::OnInputMethodChanged(ECommonInputType CommonInput)
{
	const FString InputType = UITT_InstUtil::ConvertEnumToString("ECommonInputType", CommonInput);
	ITT_LOG(TEXT("UITT_InstUtil::OnInputMathodChanged  CommonInput : %s"), *InputType);

	OnInputMethodChangeDelegate.Broadcast(CommonInput);
}
