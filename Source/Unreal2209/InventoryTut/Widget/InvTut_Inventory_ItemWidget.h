// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "../Obejct/InventoryTut_Item.h"

#include "InvTut_Inventory_ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UInvTut_Inventory_ItemWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void Init(FItemData Value);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UButton* B_Item;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UImage* I_Item;

	FItemData ItemData;
};
