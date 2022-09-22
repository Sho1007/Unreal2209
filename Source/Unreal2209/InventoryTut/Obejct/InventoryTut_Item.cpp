// Fill out your copyright notice in the Description page of Project Settings.


#include "./InventoryTut_Item.h"
#include "../Character/InventoryTut_PlayerCharacter.h"

// Sets default values
AInventoryTut_Item::AInventoryTut_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
}

// Called when the game starts or when spawned
void AInventoryTut_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInventoryTut_Item::Interact(AInventoryTut_PlayerCharacter* Character)
{
	if (Character)
	{
		Character->AddItemToInventoryidget(ItemData);
	}
	Destroy();
}
