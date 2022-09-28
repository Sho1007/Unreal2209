// Fill out your copyright notice in the Description page of Project Settings.


#include "./InventoryTut_PlayerCharacter.h"
#include "../Interface/InteractableInterface.h"
#include "./InvTut_PlayerController.h"
#include "Net/UnrealNetwork.h"

#pragma region Init

// Sets default values
AInventoryTut_PlayerCharacter::AInventoryTut_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SkeletalMesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Body(TEXT("SkeletalMesh'/Game/Resources/Mesh/Knight/knight.knight'"));

	if (SK_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Body.Object);
	}
	else
		return;

	// Component Setting

	StatusComponent = CreateDefaultSubobject<UInvTut_CharacterStatusComponet>(TEXT("StatusComponent"));
	if (!StatusComponent) return;
	StatusComponent->SetIsReplicated(true);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponet"));

	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->SetupAttachment(GetMesh());
		


	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90.0f), FQuat(FRotator(0, -90.0f, 0)));



	// HUD Setting
	InterfaceClass = nullptr;
	InterfaceWidget = nullptr;

	static ConstructorHelpers::FClassFinder<UInvTut_InterfaceWidget> Temp(TEXT("WidgetBlueprint'/Game/InventoryTut/Widgets/WBP_InvTut_Interface.WBP_InvTut_Interface_C'"));
	if (Temp.Succeeded())
	{
		InterfaceClass = Temp.Class;
	}
	else
		return;
}

// Called when the game starts or when spawned
void AInventoryTut_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create HUD Widget
	if (IsLocallyControlled() && InterfaceClass)
	{
		AInvTut_PlayerController* PC = GetController<AInvTut_PlayerController>();
		if (IsValid(PC))
		{
			InterfaceWidget = CreateWidget<UInvTut_InterfaceWidget>(PC, InterfaceClass);

			if (IsValid(InterfaceWidget))
				InterfaceWidget->AddToPlayerScreen();
		}
	}

	// Update HUD
	UpdateHUD();

	// BindDelegate
	StatusComponent->ChangeStatus.BindUFunction(this, FName("UpdateHUD"));

	if (IsLocallyControlled())
	{
		InterfaceWidget->GetInventoryWidget()->InitGrid(5, 4);
	}	
}

// Called every frame
void AInventoryTut_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryTut_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AInventoryTut_PlayerCharacter, InventoryItems, COND_OwnerOnly);
}

// Called to bind functionality to input
void AInventoryTut_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInventoryTut_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInventoryTut_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AInventoryTut_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &AInventoryTut_PlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AInventoryTut_PlayerCharacter::Interact);

	PlayerInputComponent->BindKey(EKeys::I, EInputEvent::IE_Pressed, this, &AInventoryTut_PlayerCharacter::ChangeUI);
}

#pragma endregion

#pragma region MoveSetup


void AInventoryTut_PlayerCharacter::MoveForward(float InputAxis)
{
	if ((Controller == nullptr) || (InputAxis == 0.0f)) return;

	// Find out which way is forward

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get Forward Vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, InputAxis);
}

void AInventoryTut_PlayerCharacter::MoveRight(float InputAxis)
{
	if ((Controller == nullptr) || (InputAxis == 0.0f)) return;

	// Find out which way is forward

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get Forward Vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, InputAxis);
}

#pragma endregion



void AInventoryTut_PlayerCharacter::AddHealth(float Value)
{
	if (HasAuthority())
		StatusComponent->AddHealth(Value);
}

void AInventoryTut_PlayerCharacter::RemoveHunger(float Value)
{
	StatusComponent->SubHunger(Value);
}

void AInventoryTut_PlayerCharacter::SetInventoryWidget(UUserWidget* Widget)
{
}

void AInventoryTut_PlayerCharacter::Interact()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * 1000.0f);

	if (HasAuthority())
	{
		Interact(Start, End);
	}
	else
	{
		Server_Interact(Start, End);
	}
}

void AInventoryTut_PlayerCharacter::Interact(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor()))
		{
			Interface->Interact(this);
		}
	}
}

bool AInventoryTut_PlayerCharacter::Server_Interact_Validate(FVector Start, FVector End)
{
	return true;
}

void AInventoryTut_PlayerCharacter::Server_Interact_Implementation(FVector Start, FVector End)
{
	Interact(Start, End);
}

void AInventoryTut_PlayerCharacter::ChangeUI()
{
	InterfaceWidget->ToggleSwitcherIndex();
}

void AInventoryTut_PlayerCharacter::UpdateHUD()
{
	if (IsLocallyControlled())
		if (InterfaceWidget->IsValidLowLevelFast())
			InterfaceWidget->UpdateHUD(StatusComponent->GetHealth(), StatusComponent->GetHunger());
}

void AInventoryTut_PlayerCharacter::RemoveItem(int index)
{
	if (IsLocallyControlled())
	{

	}
	else
	{
		Client_RemoveItem(index);
	}
}

void AInventoryTut_PlayerCharacter::Client_RemoveItem_Implementation(int index)
{
	InterfaceWidget->GetInventoryWidget()->ResetItemWidget();
}

#pragma region InventoryComponent

void AInventoryTut_PlayerCharacter::UseItem(TSubclassOf<AInventoryTut_Item> ItemSubclass)
{
	if (ItemSubclass)
	{
		if (HasAuthority())
		{
			// Use Item
			
			// Check Has Item
			for (int i = 0; i < InventoryItems.Num(); ++i)
			{
				if (InventoryItems[i].ItemClass == ItemSubclass)
				{
					if (AInventoryTut_Item* Item = Cast<AInventoryTut_Item>(ItemSubclass->GetDefaultObject()))
					{
						InventoryItems[i].StackCount--;
						Item->Use(this);
						if (InventoryItems[i].StackCount == 0)
						{
							RemoveItem(i);
						}
							

						break;
					}
				}
			}
			if (IsLocallyControlled())
			{
				// OnRep이 일어나지 않으므로 따로 실행해줘야함

				// 1. Status OnRep
				UpdateHUD();

				// 2. Inventory OnRep
				OnRep_InventoryItems();
			}
		}
		else
		{
			Server_UseItem(ItemSubclass);
		}


		/*
		if (HasAuthority())
		{
			for (FItemData& ItemData : InventoryItems)
			{
				if (ItemData.ItemClass == ItemSubclass)
				{
					if (AInventoryTut_Item* Item = ItemSubclass.GetDefaultObject())
					{
						ItemData.StackCount--;
						Item->Use(this);
						if (ItemData.StackCount == 0)
							RemoveItem(ItemData);
						UpdateHUD();
						break;
					}
				}
			}
			if (IsLocallyControlled())
				OnRep_InventoryItems();
		}
		else
		{
			if (AInventoryTut_Item* Item = ItemSubclass.GetDefaultObject())
			{
				Item->Use(this);
			}
			Server_UseItem(ItemSubclass);
		}
		*/
	}
}

void AInventoryTut_PlayerCharacter::Server_UseItem_Implementation(TSubclassOf<AInventoryTut_Item> ItemSubclass)
{
	UseItem(ItemSubclass);
}

bool AInventoryTut_PlayerCharacter::Server_UseItem_Validate(TSubclassOf<AInventoryTut_Item> ItemSubclass)
{
	return true;
}

void AInventoryTut_PlayerCharacter::AddInventoryItem(FItemData ItemData)
{
	if (HasAuthority())
	{
		bool bIsNewItem = true;
		for (FItemData& CurrentItemData : InventoryItems)
		{
			if (CurrentItemData.ItemClass == ItemData.ItemClass)
			{
				CurrentItemData.StackCount++;
				bIsNewItem = false;
				break;
			}
		}
		if (bIsNewItem)
		{
			InventoryItems.Add(ItemData);
		}
		if (IsLocallyControlled())
			OnRep_InventoryItems();
	}
}

void AInventoryTut_PlayerCharacter::UpdateInventoryWidget()
{
	InterfaceWidget->GetInventoryWidget()->UpdateWidget(InventoryItems);
}

void AInventoryTut_PlayerCharacter::OnRep_InventoryItems()
{
	if (!IsLocallyControlled()) return;
	UpdateInventoryWidget();
}
#pragma endregion