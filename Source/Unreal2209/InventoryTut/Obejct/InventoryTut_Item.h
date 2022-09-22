// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interface/InteractableInterface.h"

#include "InventoryTut_Item.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class AInventoryTut_Item> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ItemCost;
};

UCLASS()
class UNREAL2209_API AInventoryTut_Item : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryTut_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "TUTORIAL")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "TUTORIAL")
	FItemData ItemData;

public:
	virtual void Interact() override;

	void SetItemData(FItemData Value) { ItemData = Value; }
	FItemData GetItemData() { return ItemData; }
};