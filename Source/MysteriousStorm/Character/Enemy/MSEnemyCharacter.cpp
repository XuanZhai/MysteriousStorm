// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/System/MSEnemyTableRow.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMSEnemyCharacter::AMSEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = CurrentHealth = 100;
	EnemyID = 0;
	bIsAbilityActive = false;
}

// Called when the game starts or when spawned
void AMSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	TryReadConfig();
	for (auto Ability : PossessAbilities)
	{
		Ability->Init(this);
	}
}

void AMSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (auto Ability : PossessAbilities)
	{
		Ability->Update(DeltaTime);
		Ability->TryActivateAbility();
	}
}


void AMSEnemyCharacter::Hurt(float damage)
{
	CurrentHealth -= damage;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HurtParticle, GetActorLocation());
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy Health: %f"), CurrentHealth));
	if (CurrentHealth <= 0)
	{
		Destroy();
	}
}

bool AMSEnemyCharacter::TryReadConfig()
{
	UGameInstance* GameInstance = GetGameInstance();
	FMSEnemyTableRow EnemyConfig;
	GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetEnemyConfigByID(EnemyID, EnemyConfig);
	for (int i = 0; i < EnemyConfig.Abilities.Num(); i++)
	{
		UMSEnemyAbilityBase* Ability = NewObject<UMSEnemyAbilityBase>(this, EnemyConfig.Abilities[i]);
		PossessAbilities.Add(Ability);
	}
	return true;
}

