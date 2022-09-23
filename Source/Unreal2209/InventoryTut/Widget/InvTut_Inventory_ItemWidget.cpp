// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_Inventory_ItemWidget.h"
#include "../Character/InventoryTut_PlayerCharacter.h"

void UInvTut_Inventory_ItemWidget::Init(FItemData Value)
{
	ItemData = Value;

	I_Item->SetBrushFromTexture(ItemData.ItemImage);
}

void UInvTut_Inventory_ItemWidget::OnItemButtonClicked()
{
	Cast<AInventoryTut_PlayerCharacter>(GetOwningPlayer()->GetCharacter())->UseItem(ItemData.ItemClass);
}

void UInvTut_Inventory_ItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	B_Item->OnClicked.AddDynamic(this, &UInvTut_Inventory_ItemWidget::OnItemButtonClicked);
}