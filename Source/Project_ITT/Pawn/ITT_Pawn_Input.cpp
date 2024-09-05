// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Pawn_Input.h"

#include "PROJECT_ITT/Manager/ITT_InputManager.h"


// Sets default values
AITT_Pawn_Input::AITT_Pawn_Input()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AIControllerClass = APlayerController::StaticClass();
}

// Called when the game starts or when spawned
void AITT_Pawn_Input::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AITT_Pawn_Input::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AITT_Pawn_Input::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(NewInputComponent != PlayerInputComponent)
	{
		NewInputComponent = PlayerInputComponent;
		if(NewInputComponent == nullptr)
		{
			return;
		}
	}
	UITT_InputManager* InputManager = gInputMng.GetInstance();
	NewInputComponent->BindAxis("LEFT_AXIS_UPDOWN", InputManager, &UITT_InputManager::LeftAxisUpDown);
	NewInputComponent->BindAxis("LEFT_AXIS_LEFTRIGHT", InputManager, &UITT_InputManager::LeftAxisLeftRight);
	NewInputComponent->BindAxis("RIGHT_AXIS_UPDOWN", InputManager, &UITT_InputManager::RightAxisUpDown);
	NewInputComponent->BindAxis("RIGHT_AXIS_LEFTRIGHT", InputManager, &UITT_InputManager::RightAxisLeftRight);

	NewInputComponent->BindAxis("LEFT_AXIS_SELECT", InputManager, &UITT_InputManager::LeftAxis_Select);

	NewInputComponent->BindTouch(IE_Pressed, InputManager, &UITT_InputManager::OnTouchDown);
	NewInputComponent->BindTouch(IE_Released, InputManager, &UITT_InputManager::OnTouchUp);
	NewInputComponent->BindTouch(IE_Repeat, InputManager, &UITT_InputManager::OnTouchMove);

	NewInputComponent->BindAction("AndroidBack", IE_Pressed, InputManager, &UITT_InputManager::AndroidBack);
	NewInputComponent->BindAction("AndroidMenu", IE_Pressed, InputManager, &UITT_InputManager::AndroidMenu);

	// Todo 용섭 : 아래의 방식대로 인풋을 커스텀 하면 된다.
	NewInputComponent->BindAction("Interaction", IE_Pressed, InputManager, &UITT_InputManager::Interaction);
	
}

bool AITT_Pawn_Input::Create()
{
	if (NewInputComponent == nullptr) 
		return false;
	
	const FKey _Key = EKeys::AnyKey;

	// pressed
	FInputKeyBinding KeyBindPressed(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Pressed);
	KeyBindPressed.bConsumeInput = true;
	KeyBindPressed.bExecuteWhenPaused = false;
	KeyBindPressed.KeyDelegate.GetDelegateWithKeyForManualSet().BindWeakLambda(this, [=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, true);
	});
	NewInputComponent->KeyBindings.Add(KeyBindPressed);

	// released
	FInputKeyBinding KeyBindReleased(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Released);
	KeyBindReleased.bConsumeInput = true;
	KeyBindReleased.bExecuteWhenPaused = false;
	KeyBindReleased.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, false);
	});
	
	NewInputComponent->KeyBindings.Add(KeyBindReleased);
	bIsCreated = true;
	return true;
}

void AITT_Pawn_Input::Destroy()
{
	bIsCreated = false;
	NewInputComponent = nullptr;
}

