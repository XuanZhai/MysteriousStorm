// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCharacter.h"
#include "MSBackpackComponent.h"

// Sets default values
AMSCharacter::AMSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BackpackComponent = CreateDefaultSubobject<UMSBackpackComponent>(TEXT("BackpackComponent"));
	AttributeComponent = CreateDefaultSubobject<UMSAttributeComponent>(TEXT("AttributeComponent"));
	WeaponComponent = CreateDefaultSubobject<UMSWeaponComponent>(TEXT("WeaponComponent"));

	StormState = 0;
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

void AMSCharacter::AddStorm(uint8 StormID)
{
	StormState |= StormID;
}

void AMSCharacter::RemoveStorm(uint8 StormID)
{
	StormState &= (~StormID);
}

#pragma endregion Storm

