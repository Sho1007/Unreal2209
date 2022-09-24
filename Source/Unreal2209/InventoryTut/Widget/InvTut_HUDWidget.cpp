// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_HUDWidget.h"

void UInvTut_HUDWidget::UpdateStatus(float Health, float Hunger)
{
	FString HealthString = FString::Printf(TEXT("%d"), (int)Health);
	FString HungerString = FString::Printf(TEXT("%d"), (int)Hunger);
	TB_Health->SetText(FText::FromString(HealthString));
	TB_Hunger->SetText(FText::FromString(HungerString));
}
