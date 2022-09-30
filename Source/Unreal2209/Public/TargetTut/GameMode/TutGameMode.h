// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API ATutGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RespwanPlayer(AActor* Player);
	UFUNCTION(BlueprintCallable)
	void SetSpawnTransform(FTransform Value);

private:
	// Property
	FTransform SpawnTransform;
};
