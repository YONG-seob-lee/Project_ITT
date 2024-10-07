// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_CharacterBase.h"

#include "ITT_InstUtil.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PROJECT_ITT/Actor/Component/ITT_MontageComponent.h"
#include "PROJECT_ITT/CharacterComponent/ITT_InputHelper.h"
#include "CharacterComponent/ITT_CharacterMovementComponent.h"
#include "CharacterState/ITT_CharacterState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "StateMachine/ITT_StateMachine.h"

// Sets default values
AITT_CharacterBase::AITT_CharacterBase( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer.SetDefaultSubobjectClass<UITT_CharacterMovementComponent>( ACharacter::CharacterMovementComponentName ) )
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	
	RootCapsuleComponent = GetCapsuleComponent();
	if(RootCapsuleComponent)
	{
		RootCapsuleComponent->SetCollisionProfileName("Capsule");
		RootCapsuleComponent->BodyInstance.bLockXRotation = true;
		RootCapsuleComponent->BodyInstance.bLockYRotation = true;
	}
	
	RootSkeletalMeshComponent = GetMesh();
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->bUseAttachParentBound = true;
	}

	
	
	RootStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if(RootStaticMeshComponent)
	{
		//RootStaticMeshComponent->SetStaticMesh();
		RootStaticMeshComponent->SetupAttachment(RootComponent);
		RootSkeletalMeshComponent->SetupAttachment(RootStaticMeshComponent);
	}

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	MovementComponent = GetCharacterMovement();
	if(MovementComponent)
	{
		// Set values for character movement
		MovementComponent->JumpZVelocity = 700.f;
		MovementComponent->AirControl = 0.35f;
		MovementComponent->MaxWalkSpeed = 1000.f;
		MovementComponent->MinAnalogWalkSpeed = 20.f;
		MovementComponent->BrakingDecelerationWalking = 2000.f;
		MovementComponent->BrakingDecelerationFalling = 1500.0f;
		
		MovementComponent->bRunPhysicsWithNoController = true;
		MovementComponent->SetIsReplicated(true);
		MovementComponent->RotationRate = FRotator(0.f, 500.f, 0.f);
		MovementComponent->bUseControllerDesiredRotation = true;
		MovementComponent->bOrientRotationToMovement = true;

		JumpMaxCount = 2;
	}

	// Add Collision Box
	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphereComponent");
	if(CollisionSphereComponent)
	{
		CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AITT_CharacterBase::CollisionSphereBeginOverlap);
		CollisionSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AITT_CharacterBase::CollisionSphereEndOverlap);
		CollisionSphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
		CollisionSphereComponent->SetEnableGravity(false);
		//CollisionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//CollisionSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
		CollisionSphereComponent->SetupAttachment(RootCapsuleComponent);
	}

	// Add Render Target 2D
	SceneCaptureSpringArm = CreateDefaultSubobject<USpringArmComponent>("CaptureSpringArm");
	if(SceneCaptureSpringArm)
	{
		SceneCaptureSpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
		SceneCaptureSpringArm->TargetArmLength = 600.f;
		SceneCaptureSpringArm->SetupAttachment(RootCapsuleComponent);
	}

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
	if(SceneCaptureComponent)
	{
		SceneCaptureComponent->SetupAttachment(SceneCaptureSpringArm);
	}

	// Add Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	if(ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = 300.f;
		ProjectileMovementComponent->MaxSpeed = 300.f;
		//ProjectileMovementComponent->bRotationFollowsVelocity = true;
		//ProjectileMovementComponent->bShouldBounce = false;
	}
	
	InputHelperComponent = CreateDefaultSubobject<UITT_InputHelper>(TEXT("InputHelperComponent"));

	CreateTestSphere();
}

bool AITT_CharacterBase::Create(const FString& LabelName)
{
	SetName(LabelName);
	SetActorLabel(LabelName);

	Initialize();
	return true;
}

void AITT_CharacterBase::Destroy()
{
	CharacterName.Empty();

	Finalize();
}

void AITT_CharacterBase::Initialize()
{
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Activate();

		if(const TObjectPtr<UITT_AnimInstance> _AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
		{
			_AnimInstance->Initialize();
		}

		RootSkeletalMeshComponent->bUseAsOccluder = false;
		RootSkeletalMeshComponent->SetSimulatePhysics(false);
	}
	
	if(RootCapsuleComponent)
	{
		RootCapsuleComponent->Activate();
		RootCapsuleComponent->OnComponentBeginOverlap.Clear();
		RootCapsuleComponent->OnComponentEndOverlap.Clear();	
	}

	if(MovementComponent)
	{
		MovementComponent->Deactivate();
	}

	// Add Anim Instance
	if(const TObjectPtr<UITT_AnimInstance> _AnimInstance = Cast<UITT_AnimInstance>(RootSkeletalMeshComponent->GetAnimInstance()))
	{
		AnimInstance = _AnimInstance;
	}
	
	// Add Anim Montage
	if(const TObjectPtr<UITT_MontageComponent> NewMontageComponent = FindComponentByClass<UITT_MontageComponent>())
	{
		MontageComponent = NewMontageComponent;
		MontageComponent->SetAnimInstance(AnimInstance);
	}

	CreateCharacterStateMachine();
	SetCharacterState(EITT_CharacterState::Movement);
	
	bInitialize = true;
}

void AITT_CharacterBase::Finalize()
{
	if (CharacterStateMachine)
	{
		CharacterStateMachine->Destroy();
		CharacterStateMachine->RemoveFromRoot();
		CharacterStateMachine = nullptr;
	}
    	
	if(TestSphere)
	{
		TestSphere->Deactivate();
	}

	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Deactivate();

		if(const TObjectPtr<UITT_AnimInstance> _AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
		{
			_AnimInstance->Finalize();
		}
	}
}

TObjectPtr<UAnimInstance> AITT_CharacterBase::GetAnimInstance()
{
	if(RootSkeletalMeshComponent == nullptr)
	{
		return nullptr;
	}

	if(AnimInstance)
	{
		return AnimInstance;
	}

	return RootSkeletalMeshComponent->GetAnimInstance();
}

void AITT_CharacterBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale,
	bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = CullDistanceScale;
	LodValues.OutLineCullDistanceScale = OutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

void AITT_CharacterBase::SetActiveMovementComponent(bool bEnable) const
{
	if(MovementComponent)
	{
		MovementComponent->SetActive(bEnable);
	}
}

void AITT_CharacterBase::SetActiveProjectileMovementComponent(bool bEnable) const
{
	if(ProjectileMovementComponent)
	{
		ProjectileMovementComponent->SetActive(bEnable);
	}
}

void AITT_CharacterBase::MoveDirection(const FVector& Direction, float Scale, bool bForce) const
{
	if(MovementComponent)
	{
		MovementComponent->AddInputVector(Direction * Scale, bForce);
	}
}

void AITT_CharacterBase::SetProjectileUpdate() const
{
	if(ProjectileMovementComponent)
	{
		ProjectileMovementComponent->SetUpdatedComponent(RootSkeletalMeshComponent);
	}
}

void AITT_CharacterBase::SetProjectileVelocity(const FVector& ShootDirection) const
{
	if(ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	}
}

void AITT_CharacterBase::SetStaticMeshComponent(TObjectPtr<UStaticMesh> StaticMesh) const
{
	RootStaticMeshComponent->SetStaticMesh(StaticMesh);
}

void AITT_CharacterBase::SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const
{
	if(MovementComponent)
	{
		FHitResult Hit(1.f);
		const FVector Delta = Position - GetActorLocation();

		MovementComponent->SafeMoveUpdatedComponent(Delta, Rotator, false, Hit);
	}
}

void AITT_CharacterBase::SetRotator(const FRotator& Rotator)
{
	SetActorRotation(Rotator);
}

void AITT_CharacterBase::ClearPathFindPoints()
{
	if(PathFindingPoints == -1)
	{
		return;
	}

	PathFindingPoints = -1;
}

bool AITT_CharacterBase::CreateCharacterStateMachine()
{
	if(CharacterStateMachine || CharacterStateClasses.Num() == 0)
	{
		return false;
	}
	
	CharacterStateMachine = ITT_NewObject<UITT_StateMachine>(UITT_StateMachine::StaticClass());
	CharacterStateMachine->AddToRoot();
	CharacterStateMachine->Create();
	
	for (auto& Iter : CharacterStateClasses)
	{
		FName EnumName = UITT_InstUtil::ConvertEnumToName<EITT_CharacterState>(TEXT("EITT_CharacterState"), Iter.Key);
		CharacterStateMachine->RegistState(static_cast<int8>(Iter.Key), EnumName, Iter.Value);
	}

	return true;
}

EITT_CharacterState AITT_CharacterBase::GetCharacterState()
{
	if (CharacterStateMachine == nullptr)
	{
		return EITT_CharacterState::Deactive;
	}
	
	TWeakObjectPtr<UITT_CharacterState> CharacterState = Cast<UITT_CharacterState>(CharacterStateMachine->GetCurrentState());

	if (CharacterState != nullptr)
	{
		return CharacterState->GetCharacterState();
	}

	return EITT_CharacterState::Deactive;
}

void AITT_CharacterBase::SetCharacterState(EITT_CharacterState CharacterState, bool _bInstant)
{
	if (CharacterStateMachine == nullptr)
	{
		return;
	}
	
	CharacterStateMachine->SetState(static_cast<int32>(CharacterState), _bInstant);
	
	ITT_LOG_Verbosity(Warning, TEXT("[CharacterState] %d"), static_cast<int32>(CharacterState));
}

void AITT_CharacterBase::SetAimMode(bool bAimed)
{
	if(bAimed)
	{
		bUseControllerRotationYaw = true;	// Yaw 회전 고정.
	}
	else
	{
		bUseControllerRotationYaw = false;
	}
}

// Called when the game starts or when spawned
void AITT_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AITT_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bInitialize == false)
	{
		Initialize();
	}
}

// Called to bind functionality to input
void AITT_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputHelperComponent->SetupPlayerInputComponent(PlayerInputComponent);
}

void AITT_CharacterBase::CollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ITT_LOG(TEXT("AITT_CharacterBase::CollisionSphereBeginOverlap"));
}

void AITT_CharacterBase::CollisionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ITT_LOG(TEXT("AITT_CharacterBase::CollisionSphereEndOverlap"));
}

void AITT_CharacterBase::CreateTestSphere()
{
	TestSphere = CreateDefaultSubobject<USphereComponent>("VisibleTestComponent");
	if(TestSphere)
	{
		TestSphere->SetSphereRadius(500.f);
		TestSphere->SetGenerateOverlapEvents(false);
		TestSphere->SetEnableGravity(false);
		TestSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TestSphere->SetCollisionProfileName(TEXT("NoCollision"));
		TestSphere->SetupAttachment(RootCapsuleComponent);
		RootSkeletalMeshComponent->SetupAttachment(TestSphere);
		RootStaticMeshComponent->SetupAttachment(TestSphere);
	}
}

