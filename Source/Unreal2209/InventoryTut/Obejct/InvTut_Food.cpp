// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_Food.h"
#include "../Character/InventoryTut_PlayerCharacter.h"

AInvTut_Food::AInvTut_Food()
{
	HungerValue = 30.0f;
}

void AInvTut_Food::Use(AInventoryTut_PlayerCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Item->Use"));
	if (Character)
	{
		Character->RemoveHunger(HungerValue);
	}
}
