// Fill out your copyright notice in the Description page of Project Settings.


#include "./InventoryTut_PlayerCharacter.h"
#include "../Widget/InvTut_Inventory_ItemWidget.h"
#include "./InvTut_PlayerController.h"


// Sets default values
AInventoryTut_PlayerCharacter::AInventoryTut_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SkeletalMesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Body(TEXT("SkeletalMesh'/Game/Resources/Mesh/Paladin/Paladin_J_Nordstrom.Paladin_J_Nordstrom'"));

	if (SK_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Body.Object);
	}
	else
		return;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponet"));

	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->SetupAttachment(GetMesh());



	// Component Setting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90.0f), FQuat(FRotator(0, -90.0f, 0)));



	// HUD Setting
	HUDClass = nullptr;
	HUDWidget = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> Temp(TEXT("WidgetBlueprint'/Game/InventoryTut/Widgets/WBP_InvTut_Inventory_Item.WBP_InvTut_Inventory_Item_C'"));
	if (Temp.Succeeded())
	{
		HUDClass = Temp.Class;
	}
	else
		return;

	// Image Test

	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture_Body(TEXT("Texture2D'/Game/Resources/Textures/cloud_whale_image.cloud_whale_image'"));
	if (Texture_Body.Succeeded())
	{
		TestImage = Texture_Body.Object;
	}
	else
		return;

	static ConstructorHelpers::FClassFinder<AInventoryTut_Item> Item_Body(TEXT("Blueprint'/Game/InventoryTut/Blueprints/BP_InventoryTut_Item.BP_InventoryTut_Item_C'"));
	if (Item_Body.Succeeded())
	{
		TestClass = Item_Body.Class;
	}
	else
		return;
}

// Called when the game starts or when spawned
void AInventoryTut_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Create HUD Widget
	if (IsLocallyControlled() && HUDClass != nullptr)
	{
		AInvTut_PlayerController* PC = GetController<AInvTut_PlayerController>();
		if (IsValid(PC))
		{
			HUDWidget = CreateWidget<UUserWidget>(PC, HUDClass);

			
			ItemData.ItemCost = 500.0f;
			ItemData.ItemImage = TestImage;
			ItemData.ItemClass = TestClass;

			Cast<UInvTut_Inventory_ItemWidget>(HUDWidget)->Init(ItemData);

			if (IsValid(HUDWidget))
				HUDWidget->AddToPlayerScreen();
		}
	}
}

// Called every frame
void AInventoryTut_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

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

void AInventoryTut_PlayerCharacter::Interact()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * 1000.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor()))
		{
			Interface->Interact();
		}
	}
}

