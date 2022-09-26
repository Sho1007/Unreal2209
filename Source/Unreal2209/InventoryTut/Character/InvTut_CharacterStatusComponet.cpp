// Fill out your copyright notice in the Description page of Project Settings.


#include "./InvTut_CharacterStatusComponet.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInvTut_CharacterStatusComponet::UInvTut_CharacterStatusComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	if (GetWorld())
	{
		//GetWorld()->GetTimerManager().SetTimer(IncreaseHungerTimer, this, &UInvTut_CharacterStatusComponet::IncreaseHunger, 2.0f, true);
	}
	
}


// Called when the game starts
void UInvTut_CharacterStatusComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInvTut_CharacterStatusComponet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInvTut_CharacterStatusComponet, Health);
	DOREPLIFETIME(UInvTut_CharacterStatusComponet, Hunger);
}


// Called every frame
void UInvTut_CharacterStatusComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInvTut_CharacterStatusComponet::SetHealth(float Value)
{
	if (Value > MaxHealth)
		Health = MaxHealth;
	else if (Value < 0)
	{
		Health = 0;
		bIsDead = true;
		// TODO
		// 캐릭터 사망 시 어떻게 처리할 것인가?
	}
	else
		Health = Value;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::AddHealth(float Value)
{
	if (Value <= 0) return;
	float TotalHealth = Health + Value;

	if (TotalHealth > MaxHealth)
		Health = MaxHealth;
	else
		Health = TotalHealth;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::SubHealth(float Value)
{
	if (Value <= 0) return;

	float TotalHealth = Health - Value;

	if (TotalHealth < 0)
	{
		Health = 0;
		bIsDead = true;
	}
	else
		Health = TotalHealth;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::SetHunger(float Value)
{
	if (Value < 0)
		Hunger = 0;
	else if (Value > MaxHunger)
		Hunger = MaxHunger;
	else
		Hunger = Value;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::AddHunger(float Value)
{
	if (Value < 0) return;
	float TotalHunger = Hunger + Value;
	if (TotalHunger > MaxHunger)
		Hunger = MaxHunger;
	else
		Hunger = TotalHunger;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::SubHunger(float Value)
{
	if (Value < 0) return;
	float TotalHunger = Hunger - Value;
	if (TotalHunger < 0)
		Hunger = 0;
	else
		Hunger = TotalHunger;

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::IncreaseHunger()
{
	Hunger += 10.0f;
	UE_LOG(LogTemp, Warning, TEXT("Hunger : %f"), Hunger);

	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

void UInvTut_CharacterStatusComponet::OnRep_Status()
{
	if (ChangeStatus.IsBound()) ChangeStatus.Execute();
}

