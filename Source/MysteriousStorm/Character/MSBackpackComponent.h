// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MSBackpackComponent.generated.h"

class AMSItemActor;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent) )
class MYSTERIOUSSTORM_API UMSBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMSBackpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<TWeakPtr<AMSItemActor>> CachedPickUpList;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanPickUpThisItem(AMSItemActor* NewItem) const;


};
