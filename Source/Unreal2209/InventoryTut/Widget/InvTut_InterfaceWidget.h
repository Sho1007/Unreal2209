// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InvTut_InventoryWidget.h"
#include "Components/WidgetSwitcher.h"

#include "InvTut_InterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UInvTut_InterfaceWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UWidgetSwitcher* WS_Interface;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UUserWidget* W_CrossHair;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UInvTut_InventoryWidget* W_Inventory;

public:
	void ToggleSwitcherIndex(int index = -1);

	UInvTut_InventoryWidget* GetInventoryWidget() const { return W_Inventory; }
};