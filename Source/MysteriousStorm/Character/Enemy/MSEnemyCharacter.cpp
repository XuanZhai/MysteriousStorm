// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyCharacter.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/System/MSEnemyTableRow.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMSEnemyCharacter::AMSEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsAbilityActive = false;
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!TryReadConfig())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read enemy config"));
	}
	MaxHealth = CurrentHealth = EnemyConfig.MaxHealth;
	bIsAbilityActive = false;
	GetCharacterMovement()->MaxWalkSpeed = EnemyConfig.Speed;
	for (auto Ability : PossessAbilities)
	{
		Ability->Init(this);
	}
	HealthBarWidget->SetWidgetClass(HealthBarWidgetClass);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetPivot(FVector2d(0.5, 0.5));
	HealthBarWidget->SetDrawSize(FVector2d(150, 10));
	HealthBarWidget->SetRelativeLocation(FVector3d(0, 0, 140));
	UMSHealthBarWidget* HealthBar = Cast<UMSHealthBarWidget>(HealthBarWidget->GetUserWidgetObject());
	HealthBar->UpdateHealthBar(CurrentHealth / MaxHealth);
}

void AMSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (auto Ability : PossessAbilities)
	{
		Ability->Update(DeltaTime);
		// Ability->TryActivateAbility();
	}
}


void AMSEnemyCharacter::Hurt(float damage, bool bPlayHurtParticle)
{
	CurrentHealth -= damage;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	if (bPlayHurtParticle)UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HurtParticle, GetActorLocation());
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy Health: %f"), CurrentHealth));
	// 更新敌人血条
	UMSHealthBarWidget* HealthBar = Cast<UMSHealthBarWidget>(HealthBarWidget->GetUserWidgetObject());
	HealthBar->UpdateHealthBar(CurrentHealth / MaxHealth);

	if (CurrentHealth <= 0)
	{
		Destroy();
	}
}

bool AMSEnemyCharacter::TryReadConfig()
{
	UGameInstance* GameInstance = GetGameInstance();
	GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetEnemyConfigByID(EnemyID, EnemyConfig);
	for (int i = 0; i < EnemyConfig.Abilities.Num(); i++)
	{
		UMSEnemyAbilityBase* Ability = NewObject<UMSEnemyAbilityBase>(this, EnemyConfig.Abilities[i]);
		PossessAbilities.Add(Ability);
	}
	return true;
}
