// Fill out your copyright notice in the Description page of Project Settings.



#include "./InvTut_InventoryComponent.h"
#include "InventoryTut_PlayerCharacter.h"

// Sets default values for this component's properties
UInvTut_InventoryComponent::UInvTut_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...

	static ConstructorHelpers::FClassFinder<UInvTut_InventoryWidget> Temp(TEXT("WidgetBlueprint'/Game/InventoryTut/Widgets/WBP_InvTut_Inventory.WBP_InvTut_Inventory_C'"));
	if (Temp.Succeeded())
		InventoryWidgetClass = Temp.Class;

	
}


// Called when the game starts
void UInvTut_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
	// ...

	if (AInventoryTut_PlayerCharacter* Character = Cast<AInventoryTut_PlayerCharacter>(GetOwner()))
	{
		if (Character->IsLocallyControlled())
		{	
			//InventoryWidget = CreateWidget<UInvTut_InventoryWidget>(this, InventoryWidgetClass);
			
		}
	}
	
}


// Called every frame
void UInvTut_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInvTut_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UInvTut_InventoryComponent::OnRep_ItemArray()
{
}

