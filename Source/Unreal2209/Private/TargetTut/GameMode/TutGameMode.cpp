// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/GameMode/TutGameMode.h"

void ATutGameMode::RespwanPlayer(AActor* Player)
{
	FActorSpawnParameters Parameters;
	Parameters.Owner = Player->GetOwner();
	GetWorld()->GetFirstPlayerController()->Possess(GetWorld()->SpawnActor<APawn>(Player->GetClass(), SpawnTransform, Parameters));
}

void ATutGameMode::SetSpawnTransform(FTransform Value)
{
	SpawnTransform = Value;
}
