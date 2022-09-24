// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvTut_CharacterStatusComponet.generated.h"

DECLARE_DELEGATE(FInvTut_CharStatComp_DeleSingle);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UNREAL2209_API UInvTut_CharacterStatusComponet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvTut_CharacterStatusComponet();

	FInvTut_CharStatComp_DeleSingle ChangeStatus;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float GetHealth() { return Health; }
	void SetHealth(float Value);
	void AddHealth(float Value);
	void SubHealth(float Value);

	float GetHunger() { return Hunger; }
	void SetHunger(float Value);
	void AddHunger(float Value);
	void SubHunger(float Value);

private:
	void IncreaseHunger();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	bool bIsDead;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	float Health;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	float MaxHealth;

	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	float Hunger;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	float MaxHunger;

	FTimerHandle IncreaseHungerTimer;
};
