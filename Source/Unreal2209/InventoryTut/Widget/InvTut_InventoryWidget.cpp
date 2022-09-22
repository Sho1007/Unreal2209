// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_InventoryWidget.h"

UInvTut_InventoryWidget::UInvTut_InventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInvTut_Inventory_ItemWidget> Temp(TEXT("WidgetBlueprint'/Game/InventoryTut/Widgets/WBP_InvTut_Inventory_Item.WBP_InvTut_Inventory_Item_C'"));
	if (Temp.Succeeded())
	{
		ItemWidgetClass = Temp.Class;
	}
}

void UInvTut_InventoryWidget::AddItem(FItemData ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("cost : %f"), ItemData.ItemCost);
	UInvTut_Inventory_ItemWidget* ItemWidget = CreateWidget<UInvTut_Inventory_ItemWidget>(Gird_Inventory, ItemWidgetClass);
	ItemWidget->Init(ItemData);
	Gird_Inventory->AddChild(ItemWidget);
}
