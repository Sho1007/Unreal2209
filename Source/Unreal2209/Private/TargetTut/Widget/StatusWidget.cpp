// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/Widget/StatusWidget.h"

void UStatusWidget::ShowDeadMenu()
{
	FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(true);
	DeadMenu->SetVisibility(ESlateVisibility::Visible);
}
