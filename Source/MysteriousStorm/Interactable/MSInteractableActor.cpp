// Fill out your copyright notice in the Description page of Project Settings.


#include "MSInteractableActor.h"
#include "MysteriousStorm/Character/MSCharacter.h"

// Sets default values
AMSInteractableActor::AMSInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereTrigger->SetSphereRadius(TriggerRadius);
	SphereTrigger->SetCollisionProfileName(TEXT("StormTrigger"));

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMSInteractableActor::OnOverlapBegin);
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AMSInteractableActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AMSInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMSInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMSInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMSCharacter* CastedCharacter = Cast<AMSCharacter>(OtherActor))
	{
		bIsInteractable = true;
	}
}


void AMSInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (AMSCharacter* CastedCharacter = Cast<AMSCharacter>(OtherActor))
	{
		bIsInteractable = false;
	}
}

void AMSInteractableActor::OnInteract(AMSCharacter* InteractCharacter)
{
	if (!InteractCharacter)
	{
		return;
	}

	// Check if have enough element
}