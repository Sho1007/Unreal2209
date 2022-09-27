// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InvTut_Inventory_ItemWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
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

	virtual void NativeConstruct() override;

	void Init();
	void InitGrid(int Row, int Column);
	
	void AddItem(const FItemData* ItemData);
	void AddItem(const FItemData* ItemData, int Row, int Column);

	void SetParent(class UInvTut_InterfaceWidget* Value) { Parent = Value; }

	void UpdateWidget(const TArray<FItemData>& NewInventoryItems);
	void RemoveItemWidget(FItemData ItemData);

	UFUNCTION()
	void OnCloseButtonClicked();

protected:

private:
	/*
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, Category = "InvTut")
	UWrapBox* WB_Inventory;
	*/
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, Category = "InvTut")
	UUniformGridPanel* UGP_Inventory;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, Category = "InvTut")
	UButton* B_Close;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, Category = "InvTut")
	int CurrentRow;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite, Category = "InvTut")
	int CurrentColumn;

	int MaxRow;
	int MaxColumn;

	class UInvTut_InterfaceWidget* Parent;


	TSubclassOf<UInvTut_Inventory_ItemWidget> ItemWidgetClass;
};
