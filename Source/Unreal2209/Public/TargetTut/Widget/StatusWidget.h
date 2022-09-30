// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"

#include "StatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowDeadMenu();
	
private: 
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UCanvasPanel* DeadMenu;
};
