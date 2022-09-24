// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../Widget/InvTut_InterfaceWidget.h"
#include "InvTut_CharacterStatusComponet.h"

#include "InventoryTut_PlayerCharacter.generated.h"

UCLASS()
class UNREAL2209_API AInventoryTut_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryTut_PlayerCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Category = "TUTORIAL")
		void AddItemToInventoryidget(FItemData ItemData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void UseItem(TSubclassOf<class AInventoryTut_Item> ItemSubclass);

	void AddHealth(float Value);
	void RemoveHunger(float Value);

private:
	// Binded Function
	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);
	void Interact();
	void ChangeUI();

	UFUNCTION()
	void UpdateHUD();

private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere);
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere);
	UCameraComponent* CameraComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere);
	UInvTut_CharacterStatusComponet* StatusComponent;

	// HUD Widget Property
	TSubclassOf<UInvTut_InterfaceWidget>	InterfaceClass;
	UInvTut_InterfaceWidget*				InterfaceWidget;
};