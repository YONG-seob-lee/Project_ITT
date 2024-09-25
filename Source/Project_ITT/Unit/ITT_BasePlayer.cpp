// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_BasePlayer.h"

#include "ITT_BasePlayer_Doll.h"
#include "PROJECT_ITT/ITT_InstUtil.h"
#include "PROJECT_ITT/StateMachine/ITT_StateBase.h"

void UITT_BasePlayer::Initialize()
{
	Super::Initialize();
}

void UITT_BasePlayer::Finalize()
{
	PlayerStateMachine->Destroy();
	PlayerStateMachine->RemoveFromRoot();
	PlayerStateMachine = nullptr;
	
	Super::Finalize();
}

void UITT_BasePlayer::PostInitialize()
{
	Super::PostInitialize();
}

void UITT_BasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerStateMachine)
	{
		PlayerStateMachine->Tick(DeltaTime);
	}
}

bool UITT_BasePlayer::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	SetUnitHandle(UnitTableId);
	if(Super::CreateUnit(UnitTableId, Pos, Rot) == false)
	{
		return false;
	}

	if(CreateActionStateMachine())
	{
		AddActionState(EITT_UnitActionState::None, TEXT("None"), UITT_StateBase::StaticClass());

		// Add Action State to 'Override Function'
		//AddActionState(EITT_UnitActionState::Player_Normal, TEXT("Player_Normal"), UITT_State_PlayerNormal::StaticClass());
	}

	ChangeActionState(EITT_UnitActionState::Player_Normal);

	CreatePlayerStateMachine();

	if(CharacterBase.IsValid())
	{
		CharacterBase->SetActiveMovementComponent(true);
	}

	return true;
}

void UITT_BasePlayer::DestroyUnit()
{
	SetUnitHandle(InvalidUnitHandle);
	Super::DestroyUnit();
}

bool UITT_BasePlayer::CreatePlayerStateMachine()
{
	if(GetUnitHandle() == InvalidUnitHandle)
	{
		return false;
	}

	PlayerStateMachine = ITT_NewObject<UITT_StateMachine>(this, UITT_StateMachine::StaticClass());
	PlayerStateMachine->AddToRoot();
	PlayerStateMachine->Create();

	return true;
}

void UITT_BasePlayer::SetSelfPlayer(bool _bSelfPlayer)
{
	bSelfPlayer = _bSelfPlayer;
}

void UITT_BasePlayer::ChangePlayerState(EITT_UnitState UnitState) const
{
	if(PlayerStateMachine)
	{
		PlayerStateMachine->SetState(static_cast<int32>(UnitState));
	}
}

void UITT_BasePlayer::SetRotator(const FRotator& Rotator) const
{
	if(const TObjectPtr<AITT_CharacterBase> Character = GetCharacterBase())
	{
		Character->SetRotator(Rotator);
	}
}

void UITT_BasePlayer::SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const
{
	if(const TObjectPtr<AITT_CharacterBase> Character = GetCharacterBase())
	{
		Character->SetPositionAndRotator(Position, Rotator);
	}
}

void UITT_BasePlayer::SetActorEnableCollision(bool bUnitEnableCollision) const
{
	const TObjectPtr<AITT_CharacterBase> Character = GetCharacterBase();
	if (GetUnitHandle() != InvalidUnitHandle && IsValid(Character))
	{
		Character->SetActorEnableCollision(bUnitEnableCollision);
	}
}

void UITT_BasePlayer::ClearComponentOverlaps() const
{
	const TObjectPtr<AITT_CharacterBase> Character = GetCharacterBase();
	if (GetUnitHandle() != InvalidUnitHandle && IsValid(Character))
	{
		Character->ClearComponentOverlaps();
		Character->UpdateOverlaps();
	}
}

void UITT_BasePlayer::SetActionState(EITT_UnitActionState _ActionState) const
{
	ChangeActionState(_ActionState);
}

void UITT_BasePlayer::SetMoveSpeed(float MoveSpeed) const
{
	if(const TObjectPtr<UITT_AnimInstance> AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
	{
		AnimInstance->SetMoveSpeed(MoveSpeed);
	}
}

bool UITT_BasePlayer::DoesSocketExist(const FName& Socket) const
{
	if(CharacterBase.IsValid())
	{
		return CharacterBase->GetMesh()->DoesSocketExist(Socket);
	}

	return false;
}

void UITT_BasePlayer::AttachMeshToSocket(const FName& SocketName, const TObjectPtr<UITT_BasePlayer_Doll>& Doll)
{
	if(!Doll)
	{
		return;
	}

	const TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = Doll->GetSkeletalMeshComponent();
	if(!SkeletalMeshComponent)
	{
		return;
	}

	SkeletalMeshComponent->AttachToComponent(GetCharacterBase()->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

void UITT_BasePlayer::ChangeActionState(EITT_UnitActionState ActionType) const
{
	UITT_InstUtil::FlushPressedKeys();
	
	Super::ChangeActionState(ActionType);
}
