// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_InputHelper.h"

#include "ITT_Define.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "PROJECT_ITT/Character/ITT_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Manager/ITT_CameraManager.h"
#include "Manager/ITT_InputManager.h"


UITT_InputHelper::UITT_InputHelper()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UITT_InputHelper::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterBase = Cast<AITT_CharacterBase>(GetOwner());
}

void UITT_InputHelper::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CharacterBase->GetCharacterState() == EITT_CharacterState::Deactive)
	{
		return;
	}
	
	if (CharacterBase->GetCharacterMovement()->IsFalling())
	{
		if (CharacterBase->GetCharacterState() != EITT_CharacterState::Jump)
		{
			if (CharacterBase->JumpCurrentCount < 2)
			{
				CharacterBase->SetCharacterState(EITT_CharacterState::Jump, true);
			}
		}
		
		if (CharacterBase->GetCharacterState() != EITT_CharacterState::DoubleJump)
		{
			if (CharacterBase->JumpCurrentCount >= 2)
			{
				CharacterBase->SetCharacterState(EITT_CharacterState::DoubleJump, true);
			}
		}
	}
	else
	{
		if (CharacterBase->GetCharacterState() == EITT_CharacterState::Jump || CharacterBase->GetCharacterState() == EITT_CharacterState::DoubleJump)
		{
			CharacterBase->SetCharacterState(EITT_CharacterState::Movement, true);
		}
	}
}

void UITT_InputHelper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(CharacterBase->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UITT_InputHelper::InputMove);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UITT_InputHelper::InputStopJumping);
		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UITT_InputHelper::InputLook);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputDash);

		EnhancedInputComponent->BindAction(GroundPound_Crouch_Action, ETriggerEvent::Started, this, &UITT_InputHelper::InputGroundPound_Crouch);
		EnhancedInputComponent->BindAction(GroundPound_Crouch_Action, ETriggerEvent::Completed, this, &UITT_InputHelper::InputStopGroundPound_Crouch);

		EnhancedInputComponent->BindAction(Swing_GrindGrapple_Action, ETriggerEvent::Started, this, &UITT_InputHelper::InputSwing_GrindGrapple);

		EnhancedInputComponent->BindAction(ToggleSprintAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputToggleSprint);
		EnhancedInputComponent->BindAction(ToggleSprintAction, ETriggerEvent::Completed, this, &UITT_InputHelper::InputStopToggleSprint);
		
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputSelectDoll);
		// Ability
		EnhancedInputComponent->BindAction(Ability1_Fire_Action, ETriggerEvent::Started, this, &UITT_InputHelper::InputAbility1_Fire);

		EnhancedInputComponent->BindAction(Ability2_Aim_Action, ETriggerEvent::Started, this, &UITT_InputHelper::InputAbility2_Aim);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputInteract);

		EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputCancel);
		
		EnhancedInputComponent->BindAction(FindOtherPlayerAction, ETriggerEvent::Started, this, &UITT_InputHelper::InputFindOtherPlayer);
	}
}

void UITT_InputHelper::InputMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (APlayerController* PlayerController = Cast<APlayerController>(CharacterBase->GetController()))
	{
		if (PlayerController != nullptr)
		{
			const FRotator Rotation = PlayerController->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			CharacterBase->AddMovementInput(ForwardDirection, MovementVector.Y);
			CharacterBase->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void UITT_InputHelper::InputJump(const FInputActionValue& Value)
{
	const EITT_CharacterState CurrentState = CharacterBase->GetCharacterState();
	if(CurrentState == EITT_CharacterState::Crouch || CurrentState == EITT_CharacterState::Roll || CurrentState == EITT_CharacterState::Aim || CurrentState == EITT_CharacterState::Dash)
	{
		return;
	}
	
	CharacterBase->Jump();
}

void UITT_InputHelper::InputStopJumping(const FInputActionValue& Value)
{
	CharacterBase->StopJumping();
}
 
void UITT_InputHelper::InputLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	CharacterBase->AddControllerYawInput(LookAxisVector.X);
	CharacterBase->AddControllerPitchInput(LookAxisVector.Y);
}

void UITT_InputHelper::InputDash(const FInputActionValue& Value)
{
	const EITT_CharacterState CurrentState = CharacterBase->GetCharacterState();
	if(CurrentState == EITT_CharacterState::Roll)
	{
		return;
	}

	CharacterBase->SetCharacterState(EITT_CharacterState::Roll);
}

void UITT_InputHelper::InputGroundPound_Crouch(const FInputActionValue& Value)
{
	CharacterBase->Crouch();
	CharacterBase->SetCharacterState(EITT_CharacterState::Crouch);
}

void UITT_InputHelper::InputStopGroundPound_Crouch(const FInputActionValue& Value)
{
	CharacterBase->UnCrouch();
	CharacterBase->SetCharacterState(EITT_CharacterState::Movement);
}

void UITT_InputHelper::InputSwing_GrindGrapple(const FInputActionValue& Value)
{
	CharacterBase->UnCrouch();
	CharacterBase->SetCharacterState(EITT_CharacterState::Movement);
}

void UITT_InputHelper::InputToggleSprint(const FInputActionValue& Value)
{
	if (CanSprint())
	{
		CharacterBase->GetCharacterMovement()->MaxWalkSpeed = 2000.f;
		CharacterBase->SetCharacterState(EITT_CharacterState::Sprint, CanSprint());
	}
}

void UITT_InputHelper::InputStopToggleSprint(const FInputActionValue& Value)
{
	if (CharacterBase->GetCharacterState() == EITT_CharacterState::Sprint)
	{
		CharacterBase->GetCharacterMovement()->MaxWalkSpeed = 1000.f;
		CharacterBase->SetCharacterState(EITT_CharacterState::Movement);
	}
}

void UITT_InputHelper::InputSelectDoll(const FInputActionValue& Value)
{
	const float MovementSize = Value.Get<float>();

	ITT_LOG(TEXT("%f"), MovementSize);
	CharacterBase->SetCharacterState(EITT_CharacterState::Select);

	gInputMng.GetBindSelectDelegate().Broadcast(MovementSize);
}

void UITT_InputHelper::InputAbility1_Fire(const FInputActionValue& Value)
{
	if(CharacterBase->GetCharacterState() != EITT_CharacterState::Aim)
	{
		return;
	}
	CharacterBase->SetCharacterState(EITT_CharacterState::Fire);
	gInputMng.GetBindFireDelegate().Broadcast();
}

void UITT_InputHelper::InputAbility2_Aim(const FInputActionValue& Value)
{
	if(CharacterBase->GetCharacterState() == EITT_CharacterState::Aim)
	{
		CharacterBase->SetCharacterState(EITT_CharacterState::Movement);
	}
	else
	{
		CharacterBase->SetCharacterState(EITT_CharacterState::Aim);
	}
	
	gInputMng.GetBindAimedDelegate().Broadcast();
}

void UITT_InputHelper::InputInteract(const FInputActionValue& Value)
{
	if(CharacterBase->GetCharacterState() == EITT_CharacterState::Select)
	{
		gInputMng.GetBindPickDollDelegate().Broadcast();
	}
}

void UITT_InputHelper::InputCancel(const FInputActionValue& Value)
{
}

void UITT_InputHelper::InputFindOtherPlayer(const FInputActionValue& Value)
{
}

bool UITT_InputHelper::CanSprint() const
{
	return CharacterBase->GetCharacterState() == EITT_CharacterState::Movement;
}

