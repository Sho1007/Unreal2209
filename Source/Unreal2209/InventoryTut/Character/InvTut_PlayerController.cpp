// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_PlayerController.h"

void AInvTut_PlayerController::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = false;
	//EnableInput(this);
}

void AInvTut_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 반응은 하는데 Tick마다 호출돼서 너무 많이 호출됨
	/*
	if (PlayerInput.Get()->IsPressed(EKeys::I))
	{
		UE_LOG(LogTemp, Warning, TEXT("I Pressed"));
	}

	if (IsInputKeyDown(EKeys::I))
	{
		UE_LOG(LogTemp, Warning, TEXT("I Pressed"));
	}
	*/

	
}
