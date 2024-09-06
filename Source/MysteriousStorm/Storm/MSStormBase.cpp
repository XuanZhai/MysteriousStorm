// Fill out your copyright notice in the Description page of Project Settings.


#include "MSStormBase.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMSStormBase::AMSStormBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StormType = EMSStormType::Default;
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereTrigger->SetSphereRadius(TriggerRadius);
	SphereTrigger->SetCollisionProfileName(TEXT("StormTrigger"));

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMSStormBase::OnOverlapBegin);
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AMSStormBase::OnOverlapEnd);

	MoveType = EMSStormMoveType::Static;
	MoveDirection = FVector::ZeroVector;
	MoveSpeed = 0.0f;

	StrengthLevel = 1;
	CurrentEnergyLevel = 1;
	CurrentEnergyTime = 0.0f;
	EnergyIncreaseFactor = 1.0f;
	EnergyDecreaseFactor = 1.0f;
	EnergyRequiredTime = { 0.0f, 30.0f,90.0f, 180.0f };
}

// Called when the game starts or when spawned
void AMSStormBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld()) {
		APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
		ACharacter* Character = PC ? PC->GetCharacter() : nullptr;
		MainCharacter = Character ? Cast<AMSCharacter>(Character) : nullptr;
	}

}

// Called every frame
void AMSStormBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePosition(DeltaTime);
	UpdateEnergy(DeltaTime);
}

void AMSStormBase::UpdatePosition(float DeltaTime)
{
	if (MoveType == EMSStormMoveType::Static)
	{
		return;
	}
}

void AMSStormBase::UpdateEnergy(float DeltaTime)
{
	if (bIsCharacterInStorm)
	{
		if (CurrentEnergyLevel >= EnergyRequiredTime.Num())
		{
			return;
		}
		CurrentEnergyTime += DeltaTime*EnergyIncreaseFactor;
		if (CurrentEnergyTime >= EnergyRequiredTime[CurrentEnergyLevel])
		{
			CurrentEnergyLevel++;
			AddEffectToCharacter();
		}
	}
	else
	{
		if (CurrentEnergyTime <= 0)
		{
			return;
		}

		CurrentEnergyTime = FMath::Max(0.0f, CurrentEnergyTime- DeltaTime * EnergyDecreaseFactor);

		if (CurrentEnergyTime <= EnergyRequiredTime[CurrentEnergyLevel-1])
		{
			CurrentEnergyLevel = FMath::Max(1, CurrentEnergyLevel - 1);
			CurrentEnergyLevel == 1 ? AddEffectToCharacter() : RemoveEffectToCharacter();
		}
	}
}

void AMSStormBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMSCharacter* CastedCharacter = Cast<AMSCharacter>(OtherActor))
	{
		MainCharacter = CastedCharacter;
		AddEffectToCharacter();
		bIsCharacterInStorm = true;
	}
}

void AMSStormBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (AMSCharacter* CastedCharacter = Cast<AMSCharacter>(OtherActor))
	{
		RemoveEffectToCharacter();
		MainCharacter = nullptr;
		bIsCharacterInStorm = false;
	}
}


void AMSStormBase::AddEffectToCharacter()
{
	if (MainCharacter)
	{
		MainCharacter->AddStormEffect(EffectType,CurrentEnergyLevel);
	}
}


void AMSStormBase::RemoveEffectToCharacter()
{
	if (MainCharacter)
	{
		MainCharacter->RemoveStormEffect(EffectType);
	}
}