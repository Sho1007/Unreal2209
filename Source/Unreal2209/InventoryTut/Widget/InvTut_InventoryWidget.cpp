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

void UInvTut_InventoryWidget::InitGrid(int Row, int Column)
{
	MaxRow = Row;
	MaxColumn = Column;

	for (CurrentRow = 0; CurrentRow < MaxRow; ++CurrentRow)
	{
		for (CurrentColumn = 0; CurrentColumn < MaxColumn; ++CurrentColumn)
		{
			AddItem(nullptr, CurrentRow, CurrentColumn);
		}
	}

	CurrentRow = 0;
	CurrentColumn = 0;
}

void UInvTut_InventoryWidget::AddItem(const FItemData* ItemData)
{
	UInvTut_Inventory_ItemWidget* ItemWidget = CreateWidget<UInvTut_Inventory_ItemWidget>(UGP_Inventory, ItemWidgetClass);
	ItemWidget->Init(ItemData);
	//WB_Inventory->AddChild(ItemWidget);

	UGP_Inventory->AddChildToUniformGrid(ItemWidget, CurrentRow, CurrentColumn++);
	if (CurrentColumn >= MaxColumn)
	{
		CurrentColumn = 0;
		CurrentRow++;
	}
}

void UInvTut_InventoryWidget::AddItem(const FItemData* ItemData, int Row, int Column)
{
	UInvTut_Inventory_ItemWidget* ItemWidget = CreateWidget<UInvTut_Inventory_ItemWidget>(UGP_Inventory, ItemWidgetClass);
	ItemWidget->Init(ItemData);
	//WB_Inventory->AddChild(ItemWidget);

	UGP_Inventory->AddChildToUniformGrid(ItemWidget, Row, Column);
}

void UInvTut_InventoryWidget::UpdateWidget(const TArray<FItemData>& NewInventoryItems)
{
	TArray<UWidget*> Children = UGP_Inventory->GetAllChildren();
	for (int i = 0; i < NewInventoryItems.Num(); ++i)
	{
		bool bIsHere = false;

		for (UWidget* Child : Children)
		{
			UInvTut_Inventory_ItemWidget* ItemWidget = Cast<UInvTut_Inventory_ItemWidget>(Child);
			if (ItemWidget)
			{
				if (ItemWidget->GetItemData() == nullptr) continue;

				if (ItemWidget->GetItemData()->ItemClass == NewInventoryItems[i].ItemClass)
				{
					ItemWidget->Update();
					bIsHere = true;
					break;
				}
			}
		}

		if (!bIsHere)
		{
			// Create Widget
			AddItem(&NewInventoryItems[i]);
		}
	}
}

void UInvTut_InventoryWidget::RemoveItemWidget(FItemData ItemData)
{
	TArray<UWidget*> Children = UGP_Inventory->GetAllChildren();

	for (UWidget* Child : Children)
	{
		UInvTut_Inventory_ItemWidget* ItemWidget = Cast<UInvTut_Inventory_ItemWidget>(Child);
		if (ItemWidget)
		{
			if (ItemWidget->GetItemData() == nullptr) continue;

			if ((ItemWidget->GetItemData()->ItemClass == ItemData.ItemClass) && (ItemWidget->GetItemData()->StackCount == 0))
			{
				// Remove (함수 접근해서 destruct 해버리면 반환되기 전에 삭제돼서 오류뜰 것 같음)
				ItemWidget->RemoveFromParent();
				//ItemWidget->Destruct();
			}
		}
	}
}

void UInvTut_InventoryWidget::OnCloseButtonClicked()
{
	if (IsValid(Parent))
		Parent->ToggleSwitcherIndex(0);
}
