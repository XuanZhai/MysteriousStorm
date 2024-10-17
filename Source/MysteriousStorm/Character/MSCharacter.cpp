// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "MysteriousStorm/Storm/MSStormBase.h"
#include "MysteriousStorm/Item/MSConsumableData.h"
#include "Components/ArrowComponent.h"
#include "MSBackpackComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/System/MSGameState.h"

// Sets default values
AMSCharacter::AMSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BackpackComponent = CreateDefaultSubobject<UMSBackpackComponent>(TEXT("BackpackComponent"));
	AttributeComponent = CreateDefaultSubobject<UMSAttributeComponent>(TEXT("AttributeComponent"));
	WeaponComponent = CreateDefaultSubobject<UMSWeaponComponent>(TEXT("WeaponComponent"));
}

// Called when the game starts or when spawned
void AMSCharacter::BeginPlay()
{
	Super::BeginPlay();
	// GetArrowComponent()->SetVisibility(false);
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	BackpackComponent->OnBackpackOpened.AddUniqueDynamic(this, &AMSCharacter::DisableCharacterInput);
	BackpackComponent->OnBackpackClosed.AddUniqueDynamic(this, &AMSCharacter::EnableCharacterInput);
}

void AMSCharacter::EnableCharacterInput()
{
	GetMovementComponent()->Activate();
}


void AMSCharacter::DisableCharacterInput()
{
	GetMovementComponent()->Deactivate();
}

// Called every frame
void AMSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


#pragma region Storm

void AMSCharacter::AddStormEffect(TEnumAsByte<EMSEffect> NewEffect, int32 StormLevel)
{
	if (!BackpackComponent || !AttributeComponent)
	{
		return;
	}

	BackpackComponent->AddStormEffect(NewEffect, StormLevel);
	AttributeComponent->AddEffect(NewEffect);
}

void AMSCharacter::RemoveStormEffect(TEnumAsByte<EMSEffect> TargetEffect)
{
	if (!BackpackComponent || !AttributeComponent)
	{
		return;
	}

	BackpackComponent->RemoveStormEffect(TargetEffect);
	AttributeComponent->RemoveEffect(TargetEffect);
}

#pragma endregion Storm

#pragma region Item

bool AMSCharacter::TryUseItem(UMSItemData* ItemData)
{
	if (!ItemData)
	{
		return false;
	}

	if (ItemData->IsConsumable())
	{
		const UMSConsumableData* ConsumableData = Cast<UMSConsumableData>(ItemData);

		if (ConsumableData && ConsumableData->ConsumableType == EMSConsumableType::Health)
		{
			//if (!AttributeComponent->IsInMaxHealth())
			//{
			AttributeComponent->AddHealth(ConsumableData->Value);
			return true;
			//}
		}
	}

	return false;
}

#pragma endregion Item
