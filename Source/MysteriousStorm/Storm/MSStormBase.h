// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MSStormBase.generated.h"

class AMSCharacter;

UCLASS()
class MYSTERIOUSSTORM_API AMSStormBase : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriggerRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCharacterInStorm;

	AMSCharacter* MainCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	AMSStormBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
