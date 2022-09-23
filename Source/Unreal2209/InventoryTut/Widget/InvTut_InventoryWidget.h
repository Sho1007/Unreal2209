// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InvTut_Inventory_ItemWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"

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
	
	void AddItem(FItemData ItemData);

	void SetParent(class UInvTut_InterfaceWidget* Value) { Parent = Value; }

	UFUNCTION()
	void OnCloseButtonClicked();

protected:

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UWrapBox* WB_Inventory;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	UButton* B_Close;

	class UInvTut_InterfaceWidget* Parent;


	TSubclassOf<UInvTut_Inventory_ItemWidget> ItemWidgetClass;
};
