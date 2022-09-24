// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "InvTut_HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UInvTut_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateStatus(float Health, float Hunger);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* TB_Health;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* TB_Hunger;
};
