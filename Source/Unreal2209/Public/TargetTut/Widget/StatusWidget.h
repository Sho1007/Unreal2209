// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Button.h"

#include "StatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL2209_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	void ShowDeadMenu();
private:
	UFUNCTION()
	void OnClickedReturnButton();
	UFUNCTION()
	void OnClickedQuitButton();
	
public:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* DeadMenuSound;
private: 
	UAudioComponent* DeadMenuSoundComponent;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UCanvasPanel* DeadMenu;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* B_Return;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* B_Quit;
};
