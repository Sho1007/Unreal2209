// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_InterfaceWidget.h"

void UInvTut_InterfaceWidget::ToggleSwitcherIndex(int index)
{
	// index�� -1�� �ƴϸ� �ش� �ε����� Set
	if (index != -1)
		WS_Interface->SetActiveWidgetIndex(index);
	else
	{
		WS_Interface->SetActiveWidgetIndex((WS_Interface->GetActiveWidgetIndex() + 1) % WS_Interface->GetChildrenCount());
	}
}
