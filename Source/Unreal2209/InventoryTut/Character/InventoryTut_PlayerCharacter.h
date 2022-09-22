// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../Obejct/InventoryTut_Item.h"

#include "InventoryTut_PlayerCharacter.generated.h"

UCLASS()
class UNREAL2209_API AInventoryTut_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryTut_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);

	void Interact();


private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere);
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere);
	UCameraComponent* CameraComponent;


	// HUD Widget Property
	TSubclassOf<class UUserWidget> HUDClass;
	class UUserWidget*				HUDWidget;

	// Test용 Image Test 완료 후 즉시 지울것
	UTexture2D* TestImage;
	TSubclassOf<class AInventoryTut_Item> TestClass;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	FItemData ItemData;
};