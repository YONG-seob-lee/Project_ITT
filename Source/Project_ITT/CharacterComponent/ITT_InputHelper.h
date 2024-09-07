// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ITT_InputHelper.generated.h"


UCLASS(ClassGroup=ITTCharacterComp, meta=(BlueprintSpawnableComponent))
class PROJECT_ITT_API UITT_InputHelper : public UActorComponent
{
	GENERATED_BODY()

public:
	UITT_InputHelper();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
	// -- Move-- //
	void InputMove(const struct FInputActionValue& Value);

	void InputJump(const struct FInputActionValue& Value);
	void InputStopJumping(const struct FInputActionValue& Value);
	
	void InputLook(const struct FInputActionValue& Value);

	void InputDash(const struct FInputActionValue& Value);
	
	void InputGroundPound_Crouch(const struct FInputActionValue& Value);
	void InputStopGroundPound_Crouch(const struct FInputActionValue& Value);

	void InputSwing_GrindGrapple(const struct FInputActionValue& Value);

	void InputToggleSprint(const struct FInputActionValue& Value);
	void InputStopToggleSprint(const struct FInputActionValue& Value);
	
	void InputSelectDoll(const struct FInputActionValue& Value);
	
	// -- Ability-- //
	void InputAbility1_Fire(const struct FInputActionValue& Value);

	void InputAbility2_Aim(const struct FInputActionValue& Value);

	void InputInteract(const struct FInputActionValue& Value);

	void InputCancel(const struct FInputActionValue& Value);

	void InputFindOtherPlayer(const struct FInputActionValue& Value);

public:
	bool CanSprint() const;
	
private:
	bool bIsCreated = false;

	TWeakObjectPtr<class AITT_CharacterBase> CharacterBase;
	
	UPROPERTY(Category = InputPawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputComponent> NewInputComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// -- Move-- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GroundPound_Crouch_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Swing_GrindGrapple_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleSprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SelectAction;
	
	// -- Ability-- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Ability1_Fire_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Ability2_Aim_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CancelAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FindOtherPlayerAction;
};
