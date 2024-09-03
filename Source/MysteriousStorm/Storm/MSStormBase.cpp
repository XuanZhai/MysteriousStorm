// Fill out your copyright notice in the Description page of Project Settings.


#include "MSStormBase.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMSStormBase::AMSStormBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereTrigger->SetSphereRadius(TriggerRadius);
	SphereTrigger->SetCollisionProfileName(TEXT("StormTrigger"));

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMSStormBase::OnOverlapBegin);
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AMSStormBase::OnOverlapEnd);
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

}

void AMSStormBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(MainCharacter)
	{
		MainCharacter->AddStorm(ID);
	}
}

void AMSStormBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (MainCharacter)
	{
		MainCharacter->RemoveStorm(ID);
	}
}