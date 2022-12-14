// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TargetTut/Widget/StatusWidget.h"

#include "CharacterStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UNREAL2209_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void CreateStatusWidget(APlayerController* PC);

	UFUNCTION(BlueprintCallable)
	void RecieveDamage(float Damage);
	UFUNCTION(BlueprintCallable)
	void Heal(float HealValue);

	UFUNCTION(BlueprintCallable)
	void SetDead();

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();

	UFUNCTION()
	void Destroy();
public:
	// Property
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Health = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MaxHealth = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsDead = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsSprint = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UAnimMontage* ReactMontage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CameraShakeBase;

	// Sound Object
	UPROPERTY(EditDefaultsOnly)
	class USoundCue* DamageSoundCue;
	UPROPERTY(EditDefaultsOnly)
	class USoundCue* DeadSoundCue;
	class USoundCue* HealSoundCue;

	UAudioComponent* DeadSoundComponent;

	// Widget
	TSubclassOf<UStatusWidget> StatusWidgetClass;
	UStatusWidget* StatusWidget;
};
