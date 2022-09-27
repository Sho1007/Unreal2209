// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_Inventory_ItemWidget.h"
#include "../Character/InventoryTut_PlayerCharacter.h"

void UInvTut_Inventory_ItemWidget::Init(const FItemData* Value)
{
	ItemData = Value;

	if (ItemData == nullptr)
	{
		I_Item->SetOpacity(0.0f);
		B_Item->SetVisibility(ESlateVisibility::HitTestInvisible);
		TB_StackCount->SetText(FText::FromString(FString::Printf(TEXT(""))));
	}
	else
	{
		if (IsValid(ItemData->ItemClass) && IsValid(ItemData->ItemImage))
		{
			I_Item->SetOpacity(1.0f);
			I_Item->SetBrushFromTexture(ItemData->ItemImage);

			B_Item->SetVisibility(ESlateVisibility::Visible);
			TB_StackCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemData->StackCount)));
		}
	}
}

void UInvTut_Inventory_ItemWidget::Update()
{
	if (ItemData == nullptr) return;
	if (IsValid(ItemData->ItemClass) && IsValid(ItemData->ItemImage))
	{
		TB_StackCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemData->StackCount)));
	}
}

void UInvTut_Inventory_ItemWidget::OnItemButtonClicked()
{
	if (ItemData == nullptr) return;
	if (IsValid(ItemData->ItemClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());
		Cast<AInventoryTut_PlayerCharacter>(GetOwningPlayer()->GetCharacter())->UseItem(ItemData->ItemClass);
	}
}

void UInvTut_Inventory_ItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	B_Item->OnClicked.AddDynamic(this, &UInvTut_Inventory_ItemWidget::OnItemButtonClicked);
}