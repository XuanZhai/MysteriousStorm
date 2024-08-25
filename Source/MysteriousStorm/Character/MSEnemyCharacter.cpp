// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyCharacter.h"

// Sets default values
AMSEnemyCharacter::AMSEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMSEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMSEnemyCharacter::Hurt()
{
	Destroy();
}

