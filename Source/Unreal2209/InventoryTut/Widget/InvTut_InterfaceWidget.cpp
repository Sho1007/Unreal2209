// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_InterfaceWidget.h"
#include "Blueprint//WidgetBlueprintLibrary.h"

void UInvTut_InterfaceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	W_Inventory->SetParent(this);
}

void UInvTut_InterfaceWidget::UpdateHUD(float Health, float Hunger)
{
	if (W_HUD->IsValidLowLevelFast())
		W_HUD->UpdateStatus(Health, Hunger);
}

void UInvTut_InterfaceWidget::ToggleSwitcherIndex(int index)
{
	// index�� -1�� �ƴϸ� �ش� �ε����� Set
	if (index != -1)
		WS_Interface->SetActiveWidgetIndex(index);
	else
	{
		WS_Interface->SetActiveWidgetIndex((WS_Interface->GetActiveWidgetIndex() + 1) % WS_Interface->GetChildrenCount());
	}
	if (WS_Interface->GetActiveWidgetIndex() == 0)
	{
		// CrossHair�� ǥ�õǴ� ���
		GetOwningPlayer()->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
	}
	else if (WS_Interface->GetActiveWidgetIndex() == 1)
	{
		// Inventory�� ǥ�õǴ� ���
		GetOwningPlayer()->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		GetOwningPlayer()->SetInputMode(InputMode);
	}
}

void UInvTut_InterfaceWidget::SetInventoryWidget(UUserWidget* Widget)
{
	W_Inventory = Cast<UInvTut_InventoryWidget>(Widget);
	if (W_Inventory)
	{
		WS_Interface->AddChild(W_Inventory);
	}
}
