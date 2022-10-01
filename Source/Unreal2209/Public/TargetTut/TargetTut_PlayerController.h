// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TargetTut_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API ATargetTut_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* PossessedPawn) override;
};
