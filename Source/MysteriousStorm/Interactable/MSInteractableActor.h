// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MSInteractableActor.generated.h"

class AMSCharacter;
class UMSBackpackComponent;

USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FItemPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;
};

USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FItemPairInLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemPair> RequiredItems;
};


UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API AMSInteractableActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriggerRadius;

	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemPairInLevel> RequiredToLevelUp;

	bool bIsInteractable;

	bool bIsInteracting;

public:	
	// Sets default values for this actor's properties
	AMSInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AMSCharacter* InteractCharacter);

	bool CheckCanUpgrade(UMSBackpackComponent* Backpack) const;
};
