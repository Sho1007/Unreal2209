// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InvTut_InventoryWidget.h"
#include "InvTut_HUDWidget.h"
#include "Components/WidgetSwitcher.h"

#include "InvTut_InterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UInvTut_InterfaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UWidgetSwitcher* WS_Interface;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UInvTut_HUDWidget* W_HUD;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UInvTut_InventoryWidget* W_Inventory;

public:
	void UpdateHUD(float Health, float Hunger);
	void ToggleSwitcherIndex(int index = -1);

	UInvTut_InventoryWidget* GetInventoryWidget() const { return W_Inventory; }
};
