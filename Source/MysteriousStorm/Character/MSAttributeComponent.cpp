// Fill out your copyright notice in the Description page of Project Settings.


#include "MSAttributeComponent.h"

#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSEffectConfig.h"

// Sets default values for this component's properties
UMSAttributeComponent::UMSAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMSAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMSAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMSAttributeComponent::Hurt(ACharacter* Source, float Damage)
{
	UMSEffectConfig* EffectConfig = GetWorld()->GetGameInstance()->GetSubsystem<UMSDataTableSubsystem>()->GetEffectConfig();	
	for(auto Effect :Effects)
	{
		if(Effect==EMSEffect::SteamStormEffect)
		{
			Damage *= EffectConfig->SteamStormSelfDamageFactor;
		}
	}
	currentHealth -= Damage;
	DrawDebugString(GetWorld(), FVector(0,0,0), FString::Printf(TEXT("hurt: %f"), Damage), nullptr, FColor::Red, 0.0f, true);
}

void UMSAttributeComponent::AddEffect(EMSEffect NewEffect)
{
	Effects.Add(NewEffect);

	// TODO: Add Effect based on param.
}

void UMSAttributeComponent::RemoveEffect(EMSEffect TargetEffect)
{
	Effects.Remove(TargetEffect);

	// TODO: Remove Effect based on param.
}

void UMSAttributeComponent::AddHealth(float Value)
{
	currentHealth = FMath::Min(MaxHealth, currentHealth+Value);
}