// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "PROJECT_ITT/ITT_Define.h"
#include "ITT_Actor_Camera.generated.h"

UCLASS()
class PROJECT_ITT_API AITT_Actor_Camera : public AActor
{
	GENERATED_BODY()

public:
	AITT_Actor_Camera();

	FORCEINLINE ITT_Handle GetCameraHandle() const { return CameraHandle; }
	FORCEINLINE FVector GetForward() const { return SpringArmComponent->GetForwardVector(); }
	FORCEINLINE FVector GetCross() const { return SpringArmComponent->GetRightVector(); }
	FORCEINLINE FRotator GetRotation() const { return SpringArmComponent->GetComponentRotation(); }
	FORCEINLINE const FTransform& GetTransform() const { return CameraComponent->GetComponentTransform(); }
	FORCEINLINE void SetCameraAspectRatio(float AspectRatio) const { CameraComponent->SetAspectRatio(AspectRatio); }

	FORCEINLINE void SetFieldOfView(float FieldOfView) const { CameraComponent->SetFieldOfView(FieldOfView); }
	FORCEINLINE void SetSpringOffset(const FVector& TargetOffset) const { SpringArmComponent->SocketOffset = TargetOffset;  SpringArmComponent->TargetOffset = TargetOffset; }
	FORCEINLINE void SetCameraDistance(float Distance) const { SpringArmComponent->TargetArmLength = Distance; }
	void SetTargetPosition(const FVector& TargetPosition);
	void SetTargetRotator(const FRotator& TargetRotator);
	void RotateCamera();

	void SetRotateNative();
	void SetCameraRelativeLocation(const FVector& Location) const;
	void SetCameraRelativeRotation(const FRotator& Rotator) const;

	FORCEINLINE bool IsActivate() const { return bActivate; }
	FORCEINLINE void SetCameraType(EITT_GameCameraType _CameraType) { CameraType = _CameraType;}
	FORCEINLINE EITT_GameCameraType GetCameraType() const { return CameraType; }
	
	void SetAimMode();

protected:

	virtual void BeginPlay() override;

	void RegistAxis();

	void CameraMoveProcess();
	
	void OnAxisUpDown(float Value);
	void OnAxisLeftRight(float Value);

	
public:
	virtual void InitialInput(const FString& _CameraName);

	bool Create(const FString& _CameraName, const FVector& Position, const FVector& TargetPosition, float Fov, float AspectRatio, bool bPerspective = true);
	void Destroy();
	void PreProcess(float DeltaSeconds);
	void Active(float BlendTime = -1.f);
	void Deactive();
	
	virtual void Tick(float DeltaTime) override;

	EITT_GameCameraType CameraType = EITT_GameCameraType::None;
protected:
	UPROPERTY(Category = AITT_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(Category = AITT_Actor_Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(Category = AITT_Actor_Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	
	UPROPERTY(Category = AITT_Actor_Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CameraName;

	UPROPERTY(Category = AITT_Actor_Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxIntervalDistance = 99999.f;
	
private:
	void SetAspectRatio(float AspectRatio) const;
	
	bool bActivate = false;
	
	ITT_Handle CameraHandle = InvalidUnitHandle;
	FRotator CachedMovedCameraRotator = FRotator::ZeroRotator;
	FRotator FirstCameraRotator = FRotator::ZeroRotator;
	FVector2d CameraJoyStickDistance = FVector2d::ZeroVector;

	bool bAimed = false;
};
