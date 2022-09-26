// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_MedPack.h"
#include "../Character/InventoryTut_PlayerCharacter.h"

AInvTut_MedPack::AInvTut_MedPack()
{
	HealthValue = 10.0f;
}

void AInvTut_MedPack::Use(AInventoryTut_PlayerCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Item->Use"));
	if (Character)
	{
		Character->AddHealth(HealthValue);
	}
}
