// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InvTut_Inventory_ItemWidget.h"
#include "Components/UniformGridPanel.h"

#include "InvTut_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UInvTut_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInvTut_InventoryWidget(const FObjectInitializer& ObjectInitializer);
	
	void AddItem(FItemData ItemData);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UUniformGridPanel* Gird_Inventory;

	TSubclassOf<UInvTut_Inventory_ItemWidget> ItemWidgetClass;
};
