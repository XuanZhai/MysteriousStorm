// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCharacter.h"
#include "MysteriousStorm/Storm/MSStormBase.h"
#include "MSBackpackComponent.h"

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

void AMSCharacter::AddStorm(AMSStormBase* Storm)
{
	if (!BackpackComponent || !Storm)
	{
		return;
	}

	BackpackComponent->AddStormEffect(Storm->GetEffectType(), Storm->GetCurrentEnergyLevel());
}

void AMSCharacter::RemoveStorm(AMSStormBase* Storm)
{
	if (!BackpackComponent || !Storm)
	{
		return;
	}

	BackpackComponent->RemoveStormEffect(Storm->GetEffectType());
}

#pragma endregion Storm

