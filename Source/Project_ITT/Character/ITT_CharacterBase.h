// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "PROJECT_ITT/Actor/AnimInstance/ITT_AnimInstance.h"
#include "ITT_CharacterBase.generated.h"

UCLASS()
class PROJECT_ITT_API AITT_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AITT_CharacterBase( const FObjectInitializer& ObjectInitializer );

	
	bool Create(const FString& LabelName);
	void Destroy();

	void Initialize();
	void Finalize();
	
	TObjectPtr<UITT_AnimInstance> GetAnimInstance();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
	void SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const;
	void SetRotator(const FRotator& Rotator) const;

	void SetActiveMovementComponent(bool bEnable) const;
	void MoveDirection(const FVector& Direction, float Scale = 1.f, bool bForce = false) const;

	void SetStaticMeshComponent(TObjectPtr<UStaticMesh> StaticMesh) const;
	
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetRootSkeletalMeshComponent() const { return RootSkeletalMeshComponent; }
	FORCEINLINE FVector GetCurrentLocation() const { return GetActorLocation(); }
	FORCEINLINE FRotator GetCurrentRotator() const { return GetActorRotation(); }

	FORCEINLINE bool IsMovePathFindingPoints() const { return PathFindingPoints >= 0; }

	FORCEINLINE void SetOwnerUnitBase(TObjectPtr<class UObject> _UnitBase) { OwnerUnitBase = _UnitBase; } 
	FORCEINLINE TObjectPtr<class UObject> GetOwnerUnitBase() const { return OwnerUnitBase.Get(); }
	
	void ClearPathFindPoints();
	
	bool CreateCharacterStateMachine();
	
	EITT_CharacterState GetCharacterState();
	void SetCharacterState(EITT_CharacterState CharacterState, bool _bInstant = true);

	TMap<EITT_CharacterState, TObjectPtr<class UITT_DataAsset_SubAnimation>>& GetCharacterStateToAnimationData() { return CharacterStateToAnimationData; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void CreateTestSphere();

	FORCEINLINE void SetName(const FString& Name) { CharacterName = Name; }

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bReceive_React = false;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ReactValue = 0.f;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CharacterName = FString();
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> RootSkeletalMeshComponent = nullptr;

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> RootStaticMeshComponent = nullptr;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RootCapsuleComponent = nullptr;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> TestSphere = nullptr;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FITT_CharacterLodValues LodValues = FITT_CharacterLodValues();

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UITT_MontageComponent> MontageComponent = nullptr;

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> CollisionSphereComponent = nullptr;

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SceneCaptureSpringArm = nullptr;

	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneCaptureComponent2D> SceneCaptureComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UITT_InputHelper> InputHelperComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<UITT_AnimInstance> AnimInstance = nullptr;
	
	TWeakObjectPtr<UObject> OwnerUnitBase = nullptr;
	
	bool bInitialize = false;
	int32 PathFindingPoints = 0;

	TObjectPtr<class UITT_StateMachine> CharacterStateMachine = nullptr;

	UPROPERTY(EditAnywhere)
	TMap<EITT_CharacterState, TSubclassOf<class UITT_CharacterState>> CharacterStateClasses;

	UPROPERTY(Category = Anim, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EITT_CharacterState, TObjectPtr<class UITT_DataAsset_SubAnimation>> CharacterStateToAnimationData;
};
