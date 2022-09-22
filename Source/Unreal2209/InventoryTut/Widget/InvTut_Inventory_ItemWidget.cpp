// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_Inventory_ItemWidget.h"

void UInvTut_Inventory_ItemWidget::Init(FItemData Value)
{
	ItemData = Value;

	I_Item->SetBrushFromTexture(ItemData.ItemImage);
}
