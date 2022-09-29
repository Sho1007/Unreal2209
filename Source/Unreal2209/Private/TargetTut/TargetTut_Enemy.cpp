// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/TargetTut_Enemy.h"

// Sets default values
ATargetTut_Enemy::ATargetTut_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetTut_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetTut_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATargetTut_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

