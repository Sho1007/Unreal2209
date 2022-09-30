// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "TargetTut_Character.generated.h"

UCLASS()
class UNREAL2209_API ATargetTut_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATargetTut_Character();

protected:
	// Called when the game starts or when spawnedx
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Bind Input
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);

#pragma region LockOn
public:
	// Targeting Fucntion

	UFUNCTION(BlueprintCallable)
	void LockOnTarget();
	UFUNCTION(BlueprintCallable)
	void LockOnLeftTarget();
	UFUNCTION(BlueprintCallable)
	void LockOnRightTarget();

	UFUNCTION(BlueprintCallable)
	void FindTargets(int32 Direction);
	UFUNCTION(BlueprintCallable)
	void FindNearTargets(bool& bHasTargets, TArray<AActor*>& Targets);
	UFUNCTION(BlueprintCallable)
	void SetPotentialTargets(bool bHasTargets, TArray<AActor*> Targets);

	UFUNCTION(BlueprintCallable)
	void GetIsForward(FVector TargetLocation, float& Result);
	UFUNCTION(BlueprintCallable)
	void GetIsLeft(FVector TargetLocation, float& Result);

	UFUNCTION(BlueprintCallable)
	void SelectForwardTarget();
	UFUNCTION(BlueprintCallable)
	void SelectLeftTarget();
	UFUNCTION(BlueprintCallable)
	void SelectRightTarget();

	UFUNCTION(BlueprintCallable)
	void LockCameraToTarget();
	UFUNCTION(BlueprintCallable)
	void LockOnCamera();
	UFUNCTION(BlueprintCallable)
	void LockOff();

	UFUNCTION(BlueprintCallable)
	void ChekcRange();

	// Targeting Property
	UPROPERTY(BlueprintReadWrite)
	AActor* TargetLocked;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> PotentialTargets;

	TSubclassOf<UObject> TargetClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TargetSearchRadius = 1300.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TargetSearchDegrees = 45.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bDebugModeActive = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsLockOn = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsCameraLocked = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FTimerHandle RangeCheckTimer;
#pragma endregion

private:
	// Character Components
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditDefaultsOnly)
	UCameraComponent* CameraComponent;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;
};
