// Fill out your copyright notice in the Description page of Project Settings.


#include "./InventoryTut_PlayerCharacter.h"
#include "../Interface/InteractableInterface.h"
#include "./InvTut_PlayerController.h"


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

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponet"));

	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->SetupAttachment(GetMesh());



	// Component Setting
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
	if (IsLocallyControlled() && InterfaceClass != nullptr)
	{
		AInvTut_PlayerController* PC = GetController<AInvTut_PlayerController>();
		if (IsValid(PC))
		{
			InterfaceWidget = CreateWidget<UInvTut_InterfaceWidget>(PC, InterfaceClass);

			if (IsValid(InterfaceWidget))
				InterfaceWidget->AddToPlayerScreen();
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

	PlayerInputComponent->BindKey(EKeys::I, EInputEvent::IE_Pressed, this, &AInventoryTut_PlayerCharacter::ChangeUI);
}

void AInventoryTut_PlayerCharacter::AddItemToInventoryidget(FItemData ItemData)
{
	InterfaceWidget->GetInventoryWidget()->AddItem(ItemData);
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
			Interface->Interact(this);
		}
	}
}

void AInventoryTut_PlayerCharacter::ChangeUI()
{
	InterfaceWidget->ToggleSwitcherIndex();
}

