// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_InventoryWidget.h"
#include "./InvTut_InterfaceWidget.h"

UInvTut_InventoryWidget::UInvTut_InventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInvTut_Inventory_ItemWidget> Temp(TEXT("WidgetBlueprint'/Game/InventoryTut/Widgets/WBP_InvTut_Inventory_Item.WBP_InvTut_Inventory_Item_C'"));
	if (Temp.Succeeded())
	{
		ItemWidgetClass = Temp.Class;
	}

}

void UInvTut_InventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UInvTut_InventoryWidget::Init()
{
	B_Close->OnClicked.AddDynamic(this, &UInvTut_InventoryWidget::OnCloseButtonClicked);
}

void UInvTut_InventoryWidget::AddItem(FItemData ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("cost : %f"), ItemData.ItemCost);
	UInvTut_Inventory_ItemWidget* ItemWidget = CreateWidget<UInvTut_Inventory_ItemWidget>(WB_Inventory, ItemWidgetClass);
	ItemWidget->Init(ItemData);
	WB_Inventory->AddChild(ItemWidget);
}

void UInvTut_InventoryWidget::OnCloseButtonClicked()
{
	if (IsValid(Parent))
		Parent->ToggleSwitcherIndex(0);
}
