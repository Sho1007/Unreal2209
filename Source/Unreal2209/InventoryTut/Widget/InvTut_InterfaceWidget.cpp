// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_InterfaceWidget.h"

void UInvTut_InterfaceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	W_Inventory->SetParent(this);
}

void UInvTut_InterfaceWidget::ToggleSwitcherIndex(int index)
{
	// index가 -1이 아니면 해당 인덱스로 Set
	if (index != -1)
		WS_Interface->SetActiveWidgetIndex(index);
	else
	{
		WS_Interface->SetActiveWidgetIndex((WS_Interface->GetActiveWidgetIndex() + 1) % WS_Interface->GetChildrenCount());
	}
	if (WS_Interface->GetActiveWidgetIndex() == 0)
	{
		// CrossHair가 표시되는 경우
		GetOwningPlayer()->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
	}
	else if (WS_Interface->GetActiveWidgetIndex() == 1)
	{
		// Inventory가 표시되는 경우
		GetOwningPlayer()->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
	}
}
