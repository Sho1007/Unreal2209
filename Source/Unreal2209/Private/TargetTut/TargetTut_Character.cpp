// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTut/TargetTut_Character.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TargetTut/TargetTut_EnemyInterface.h"
#include "TargetTut/TargetTut_Enemy.h"

// Sets default values
ATargetTut_Character::ATargetTut_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	static ConstructorHelpers::FClassFinder<UObject> Temp(TEXT("Blueprint'/Game/TargetTut/Blueprints/BP_TestEnemy.BP_TestEnemy_C'"));
	if (Temp.Succeeded())
		TargetClass = Temp.Class;
}

// Called when the game starts or when spawned
void ATargetTut_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetTut_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATargetTut_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATargetTut_Character::LockOnTarget()
{
	if (!bIsLockOn)
	{
		FindTargets(0);
		if (TargetLocked && TargetLocked->IsValidLowLevelFast())
		{
			LockOnCamera();
		}
		else
		{
			// TODO

			// 대상이 없다고 화면에 글자 표시?
		}
	}
	else
	{
		LockOff();
	}
}

void ATargetTut_Character::LockOnLeftTarget()
{
	if (bIsLockOn)
	{

	}
	else
	{

	}
}

void ATargetTut_Character::FindTargets(int32 Direction)
{
	bool bHasTargets = false;
	TArray<AActor*> Targets;
	FindNearTargets(bHasTargets, Targets);
	SetPotentialTargets(bHasTargets, Targets);
	
	if (PotentialTargets.Num())
	{
		switch (Direction)
		{
		case 0:
			SelectForwardTarget();
			break;
		case 1:
			SelectLeftTarget();
			break;
		case 2:
			SelectRightTarget();
			break;
		}
	}
}

void ATargetTut_Character::FindNearTargets(bool& bHasTargets, TArray<AActor*>& Targets)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryArray;
	QueryArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorArray;
	ActorArray.Add(this);
	bHasTargets = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), TargetSearchRadius, QueryArray, ATargetTut_Enemy::StaticClass(), ActorArray, Targets);

	if (bDebugModeActive)
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), GetActorLocation(), TargetSearchRadius, 12, FLinearColor(0, 1, 0), 5.0f, 5.0f);
}

void ATargetTut_Character::SetPotentialTargets(bool bHasTargets, TArray<AActor*> Targets)
{
	if (!bHasTargets) return;

	PotentialTargets.Empty();

	for (AActor* Target : Targets)
	{

		if (Target->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			if (!ITargetTut_EnemyInterface::Execute_IsEnemyDead(Target))
			{
				float Result;
				GetIsForward(Target->GetActorLocation(), Result);
				if (Result > UKismetMathLibrary::DegCos(TargetSearchDegrees))
					PotentialTargets.AddUnique(Target);
			}
		}
	}
}

void ATargetTut_Character::GetIsForward(FVector TargetLocation, float& Result)
{
	
	FVector PlayerToTarget = TargetLocation - CameraComponent->GetComponentLocation();

	Result = (PlayerToTarget.Dot(CameraComponent->GetForwardVector()) / PlayerToTarget.Length());
}

void ATargetTut_Character::GetIsLeft(FVector TargetLocation, float& Result)
{
	FVector CameraToTarget = TargetLocation - CameraComponent->GetComponentLocation();

	FVector CrossVector = CameraToTarget.Cross(CameraComponent->GetForwardVector());

	Result = CrossVector.Dot(CameraComponent->GetUpVector());
}

void ATargetTut_Character::SelectForwardTarget()
{
	float MaxValue = 0.0f;
	AActor* SelectedActor = nullptr;
	for (AActor* Target : PotentialTargets)
	{
		float Result;
		GetIsForward(Target->GetActorLocation(), Result);

		if (Result > MaxValue)
		{
			MaxValue = Result;
			SelectedActor = Target;
		}
	}
	if (SelectedActor && SelectedActor->IsValidLowLevelFast())
	{
		TargetLocked = SelectedActor;
	}
}

void ATargetTut_Character::SelectLeftTarget()
{
	float MinValue = 1000.0f;
	AActor* SelectedActor = nullptr;
	for (AActor* Target : PotentialTargets)
	{
		if (Target == TargetLocked) continue;

		float Result;
		GetIsLeft(Target->GetActorLocation(), Result);

		if (Result > 0)
		{
			if (Result < MinValue)
			{
				MinValue = Result;
				SelectedActor = Target;
			}
		}
	}
	if (SelectedActor && SelectedActor->IsValidLowLevelFast())
	{
		if (TargetLocked->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(TargetLocked, false);

		}
		if (SelectedActor->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(SelectedActor, true);
		}

		TargetLocked = SelectedActor;
	}
}

void ATargetTut_Character::SelectRightTarget()
{
	float MaxValue = -1000.0f;
	AActor* SelectedActor = nullptr;
	for (AActor* Target : PotentialTargets)
	{
		if (Target == TargetLocked) continue;

		float Result;
		GetIsLeft(Target->GetActorLocation(), Result);

		if (Result < 0)
		{
			if (Result > MaxValue)
			{
				MaxValue = Result;
				SelectedActor = Target;
			}
		}
	}
	if (SelectedActor && SelectedActor->IsValidLowLevelFast())
	{
		if (TargetLocked->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(TargetLocked, false);

		}
		if (SelectedActor->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(SelectedActor, true);
		}

		TargetLocked = SelectedActor;
	}
}

void ATargetTut_Character::LockOnCamera()
{
	SpringArmComponent->bEnableCameraRotationLag = true;
	bIsLockOn = true;
	bIsCameraLocked = true;

	if (TargetLocked && TargetLocked->IsValidLowLevelFast())
	{
		if (TargetLocked->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
		{
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(TargetLocked, true);

			GetWorld()->GetTimerManager().SetTimer(RangeCheckTimer, this, &ATargetTut_Character::ChekcRange,1.0f, true);
		}
	}
	else
	{
		LockOff();
	}

}

void ATargetTut_Character::LockOff()
{
	GetWorld()->GetTimerManager().ClearTimer(RangeCheckTimer);
	RangeCheckTimer.Invalidate();

	PotentialTargets.Empty();
	bIsLockOn = false;
	bIsCameraLocked = false;
	if (TargetLocked && TargetLocked->IsValidLowLevelFast())
		if (TargetLocked->GetClass()->ImplementsInterface(UTargetTut_EnemyInterface::StaticClass()))
			ITargetTut_EnemyInterface::Execute_SetTargetWidget(TargetLocked, false);
	TargetLocked = nullptr;

	FRotator Rotator = GetActorRotation();
	Rotator.Pitch = -10.0f;

	GetController()->SetControlRotation(Rotator);

	SpringArmComponent->bEnableCameraRotationLag = false;
}

void ATargetTut_Character::ChekcRange()
{
	if (TargetLocked && TargetLocked->IsValidLowLevelFast())
	{
		if (GetDistanceTo(TargetLocked) > TargetSearchRadius * 1.5f)
		{
			LockOff();
		}
	}
	else
		LockOff();
}

