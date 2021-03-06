// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PaperCharacter.h"
#include "FlintCharacter.generated.h"

// This class is the default character for Flint, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals

class UTextRenderComponent;

UCLASS(config=Game)
class AFlintCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;

	// Jump function overrides

	virtual void Jump() override;

	virtual void StopJumping() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual bool CanJumpInternal_Implementation() const override;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;


	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	// Called for sprint input
	UFUNCTION(BlueprintCallable)
	void Dash();

	// How fast the dash should be
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashMultiplier;

	// How long before dash comes off cooldown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashCooldownTime;


	// Maximum number of multi-jumps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MaxJumpCount;

	// Maximum jump time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxJumpTime;

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AFlintCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	// TODO: This is certainly not the best implementation of a cooldown haha

	// Check the cooldown state for dash
	bool GetDashCooldown();

	// Set the Dash cooldown start time
	void StartDashCooldown();

	// Set the dash cooldown state
	void SetDashCooldown(bool CooldownState);

	// The state of the dash cooldown
	bool bDashCooldown;

	// Set the current jump count
	void SetCurrentJumpCount(int NewJumpCount);

	// Get the current jump count
	int GetCurrentJumpCount();

	// Set the max jump count
	void SetMaxJumpCount(int NewMaxJumpCount);

	// Get the max jump count
	int GetMaxJumpCount();

	// Current number of jumps
	UPROPERTY()
	int CurrentJumpCount;

	// Handle for the dash cooldown timer
	FTimerHandle DashTimerHandle;

};
