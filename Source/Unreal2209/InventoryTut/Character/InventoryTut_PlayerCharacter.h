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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override ;

public:
	void AddInventoryItem(FItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void UseItem(TSubclassOf<AInventoryTut_Item> ItemSubclass);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseItem(TSubclassOf<AInventoryTut_Item> ItemSubclass);

	void AddHealth(float Value);
	void RemoveHunger(float Value);

protected:
	UFUNCTION(Category = "TUTORIAL")
	void UpdateInventoryWidget();

private:
	// Binded Function
	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);

	void Interact();
	void Interact(FVector Start, FVector End);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interact(FVector Start, FVector End);

	void ChangeUI();

	UFUNCTION()
	void UpdateHUD();

	// Replicate
	UPROPERTY(ReplicatedUsing = OnRep_InventoryItems, meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	TArray<FItemData> InventoryItems;

	UFUNCTION()
	void OnRep_InventoryItems();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	UInvTut_CharacterStatusComponet* StatusComponent;

	// HUD Widget Property
	TSubclassOf<UInvTut_InterfaceWidget>	InterfaceClass;
	UInvTut_InterfaceWidget*				InterfaceWidget;
};