// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackComponent.h"

// Sets default values for this component's properties
UMSBackpackComponent::UMSBackpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMSBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMSBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UMSBackpackComponent::CanPickUpThisItem(AMSItemActor* NewItem) const
{
	if (!NewItem)
	{
		return false;
	}

	return true;
}