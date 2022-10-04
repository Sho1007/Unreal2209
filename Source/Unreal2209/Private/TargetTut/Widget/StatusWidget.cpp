// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/Widget/StatusWidget.h"
#include "TargetTut/CharacterStatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	B_Return->OnClicked.AddDynamic(this, &UStatusWidget::OnClickedReturnButton);
	B_Quit->OnClicked.AddDynamic(this, &UStatusWidget::OnClickedQuitButton);
}

void UStatusWidget::ShowDeadMenu()
{
	if (DeadMenuSound && DeadMenuSound->IsValidLowLevelFast())
		DeadMenuSoundComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DeadMenuSound);
	else
		UE_LOG(LogTemp, Warning, TEXT("[%s][StatusWidget] DeadMenuSound Is Not Valid"), *GetOwningPlayerPawn()->GetName());
	FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(true);
	DeadMenu->SetVisibility(ESlateVisibility::Visible);
}

void UStatusWidget::OnClickedReturnButton()
{
	UCharacterStatusComponent* StatusComponent = Cast<UCharacterStatusComponent>(GetOwningPlayerPawn()->GetComponentByClass(UCharacterStatusComponent::StaticClass()));
	if (StatusComponent && StatusComponent->IsValidLowLevelFast())
	{
		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->SetShowMouseCursor(false);
		DeadMenu->SetVisibility(ESlateVisibility::Hidden);

		if (DeadMenuSoundComponent && DeadMenuSoundComponent->IsValidLowLevelFast())
		{
			DeadMenuSoundComponent->Stop();
		}
			

		StatusComponent->RespawnPlayer();
	}
}

void UStatusWidget::OnClickedQuitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Type::Quit, false);
}
