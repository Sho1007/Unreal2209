// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Widget/InvTut_InventoryWidget.h"

#include "InvTut_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class UNREAL2209_API UInvTut_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvTut_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_ItemArray();

	UPROPERTY(ReplicatedUsing = OnRep_ItemArray)
	TArray<FItemData> ItemArray;

	TSubclassOf<UInvTut_InventoryWidget> InventoryWidgetClass;
	UPROPERTY()
	UInvTut_InventoryWidget* InventoryWidget;
};
