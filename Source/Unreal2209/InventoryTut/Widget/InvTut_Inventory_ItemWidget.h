// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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
	virtual void NativeConstruct() override;

	void Init(const FItemData* Value);

	void Update();

	UFUNCTION()
	void OnItemButtonClicked();

	const FItemData* GetItemData() { return ItemData; }

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UButton* B_Item;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UImage* I_Item;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UTextBlock* TB_StackCount;

	const FItemData* ItemData = nullptr;
};
