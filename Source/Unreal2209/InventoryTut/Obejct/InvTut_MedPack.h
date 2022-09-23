// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./InventoryTut_Item.h"
#include "InvTut_MedPack.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API AInvTut_MedPack : public AInventoryTut_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "TUTORIAL")
	float HealthValue;


public:
	AInvTut_MedPack();

	virtual void Use(class AInventoryTut_PlayerCharacter* Character) override;
};
