// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/CharacterStatusComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "TargetTut/GameMode/TutGameMode.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	static ConstructorHelpers::FObjectFinder<USoundCue> DamageSoundCue_Body(TEXT("SoundCue'/Game/Resources/SFX/DamageSoundCue.DamageSoundCue'"));
	if (DamageSoundCue_Body.Succeeded())
		DamageSoundCue = DamageSoundCue_Body.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundCue> DeadSoundCue_Body(TEXT("SoundCue'/Game/Resources/SFX/DeadSoundCue.DeadSoundCue'"));
	if (DeadSoundCue_Body.Succeeded())
		DeadSoundCue = DeadSoundCue_Body.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> HealSoundCue_Body(TEXT("SoundCue'/Game/Resources/SFX/HealSoundCue.HealSoundCue'"));
	if (HealSoundCue_Body.Succeeded())
		HealSoundCue = HealSoundCue_Body.Object;

	static ConstructorHelpers::FClassFinder<UStatusWidget> StatusWidget_Body(TEXT("WidgetBlueprint'/Game/Damage_Healing/Widgets/WBP_Status.WBP_Status_C'"));
	if (StatusWidget_Body.Succeeded())
		StatusWidgetClass = StatusWidget_Body.Class;
}


// Called when the game starts
void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ATutGameMode* GameMode = Cast<ATutGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetSpawnTransform(GetOwner()->GetTransform());

	CreateStatusWidget(Cast<APlayerController>(GetOwner()->GetOwner()));
}


// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStatusComponent::CreateStatusWidget(APlayerController* PC)
{
	StatusWidget = CreateWidget<UStatusWidget>(PC, StatusWidgetClass);
	if (StatusWidget && StatusWidget->IsValidLowLevelFast())
	{
		StatusWidget->AddToViewport();
	}
}

void UCharacterStatusComponent::RecieveDamage(float Damage)
{
	if (bIsDead) return;
	else
	{
		Health = FMath::Clamp(Health - Damage, 0, MaxHealth);

		if (Health == 0)
		{
			if (DeadSoundCue && DeadSoundCue->IsValidLowLevelFast())
				DeadSoundComponent = UGameplayStatics::SpawnSoundAttached(DeadSoundCue, GetOwner()->GetRootComponent());
			else
				UE_LOG(LogTemp, Warning, TEXT("[%s][CharacterStatusComponent] DeadSoundCue Is Not Valid"), *GetOwner()->GetName());
			
			SetDead();
		}
		else
		{
			if (DamageSoundCue && DamageSoundCue->IsValidLowLevelFast())
				UGameplayStatics::SpawnSoundAttached(DamageSoundCue, GetOwner()->GetRootComponent(), FName("None"), FVector(0, 0, 0), EAttachLocation::KeepRelativeOffset, false, 1.0f, 1.0f, 0.3f);
			else
				UE_LOG(LogTemp, Warning, TEXT("[%s][CharacterStatusComponent] DamageSoundCue Is Not Valid"), *GetOwner()->GetName());

			if (ReactMontage && ReactMontage->IsValidLowLevelFast())
			{
				Cast<ACharacter>(GetOwner())->PlayAnimMontage(ReactMontage);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("[%s][CharacterStatusComponent] ReactMontage Is Not Valid"), *GetOwner()->GetName());
			if (CameraShakeBase && CameraShakeBase->IsValidLowLevelFast())
			{
				Cast<APlayerController>(GetOwner()->GetOwner())->PlayerCameraManager.Get()->StartCameraShake(CameraShakeBase);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[%s][CharacterStatusComponent] CameraShakeBase Is Not Valid"), *GetOwner()->GetName());
			}
		}
	}
}

void UCharacterStatusComponent::Heal(float HealValue)
{
	if (bIsDead) return;
	else
	{
		Health = FMath::Clamp(Health + HealValue, 0, MaxHealth);
		if (HealSoundCue && HealSoundCue->IsValidLowLevelFast())
			UGameplayStatics::SpawnSoundAttached(HealSoundCue, GetOwner()->GetRootComponent());
		else
			UE_LOG(LogTemp, Warning, TEXT("[%s][CharacterStatusComponent] HealSoundCue Is Not Valid"), *GetOwner()->GetName());
	}
}

void UCharacterStatusComponent::SetDead()
{
	bIsDead = true;
	UCameraComponent* PlayerMainCamera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	if (PlayerMainCamera && PlayerMainCamera->IsValidLowLevelFast())
	{
		PlayerMainCamera->PostProcessSettings.bOverride_ColorSaturation = true;
		PlayerMainCamera->PostProcessSettings.ColorSaturation = FVector4(0, 0, 0, 1);
	}
	if (StatusWidget && StatusWidget->IsValidLowLevelFast())
	{
		StatusWidget->ShowDeadMenu();
	}
		

}

void UCharacterStatusComponent::RespawnPlayer()
{
	ATutGameMode* GameMode = Cast<ATutGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (DeadSoundComponent && DeadSoundComponent->IsValidLowLevelFast())
	{
		DeadSoundComponent->Stop();
	}

	GameMode->RespwanPlayer(GetOwner());

	GetOwner()->Destroy();
}

