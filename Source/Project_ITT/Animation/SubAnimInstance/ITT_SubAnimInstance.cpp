// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_SubAnimInstance.h"

#include "Character/ITT_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"


UITT_SubAnimInstance::UITT_SubAnimInstance()
: bShouldMove(false), Velocity(FVector::ZeroVector), GroundSpeed(0.f), GroundSpeedPerMaxJogSpeed(0.f)
, MinSpeed(0.f), MaxSpeed(500.f)
, ForwardVector(FVector::ZeroVector), FaceYaw_Cached(0.f), FaceYaw_Target(0.f), FaceYaw(0.f)
{
}

void UITT_SubAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (GetOwningActor())
	{
		CharacterBase = Cast<AITT_CharacterBase>(GetOwningActor());
	}
	 
	if (CharacterBase == nullptr)
	{
		return;
	}

	if (CharacterBase->GetCharacterMovement())
	{
		CharacterMovement = Cast<UCharacterMovementComponent>(CharacterBase->GetCharacterMovement());
	}
}

void UITT_SubAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterBase != nullptr && CharacterMovement != nullptr)
	{
		bShouldMove = CharacterMovement->GetCurrentAcceleration() != FVector::Zero() && GroundSpeed > MinSpeed;
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] ShouldMove : %d"), bShouldMove ? 1 : 0);

		
		// -- Moving -- //
		Velocity = CharacterMovement->Velocity;
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] Velocity : %f, %f, %f"), Velocity.X, Velocity.Y, Velocity.Z);
		
		GroundSpeed = Velocity.Size2D();
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] GroundSpeed : %f"), GroundSpeed);

		GroundSpeedPerMaxJogSpeed = GroundSpeed / MaxSpeed;
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] GroundSpeedPerMaxJogSpeed : %f"), GroundSpeedPerMaxJogSpeed);
		
		bShouldMove = CharacterMovement->GetCurrentAcceleration() != FVector::Zero() && GroundSpeed > MinSpeed;
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] ShouldMove : %d"), bShouldMove ? 1 : 0);

		
		// -- Direction -- //
		ForwardVector = CharacterBase->GetActorForwardVector();
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] ForwardVector : %f, %f, %f"), ForwardVector.X, ForwardVector.Y, ForwardVector.Z);
		
		ControlRotation = CharacterBase->GetControlRotation();
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] ControlRotation : %f, %f, %f"), ControlRotation.Roll, ControlRotation.Pitch, ControlRotation.Yaw);
		
		ActorRotation = CharacterBase->GetActorRotation();
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] ActorRotation : %f, %f, %f"), ActorRotation.Roll, ActorRotation.Pitch, ActorRotation.Yaw);
		
		FaceYaw_Target = ActorRotation.Yaw - ControlRotation.Yaw;
		if (FaceYaw_Target > 180.f)
		{
			FaceYaw_Target -= 360.f;
		}
		else if (FaceYaw_Target < -180.f)
		{
			FaceYaw_Target += 360.f;
		}

		if (FaceYaw_Target > 80.f || FaceYaw_Target < -80.f)
		{
			FaceYaw_Target = 0.f;
		}
		
		FaceYaw_Target *= 0.66;
		FaceYaw_Target = FMath::Clamp(FaceYaw_Target, -60.f, 60.f);
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] FaceYaw_Target : %f"), FaceYaw_Target);

		FaceYaw = FaceYaw_Cached + (FaceYaw_Target - FaceYaw_Cached) * (DeltaSeconds / 0.2f);
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] FaceYaw_Cached : %f"), FaceYaw_Cached);
		ITT_LOG_Verbosity(Warning, TEXT("[Animation] FaceYaw : %f"), FaceYaw);
		
		FaceYaw_Cached = FaceYaw;
	}
}
