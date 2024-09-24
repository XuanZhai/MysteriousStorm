// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MSStormBase.generated.h"

class AMSCharacter;
enum EMSEffect : uint8;

UENUM(BlueprintType)
enum EMSStormType : uint8
{
	DefaultStorm = 0,
	SteamStorm = 1 UMETA(DisplayName = "SteamStorm"),
};

UENUM(BlueprintType)
enum EMSStormMoveType : uint8
{
	Static = 0 UMETA(DisplayName = "StaticPosition"),
	ToBase = 1 UMETA(DisplayName = "MoveTowardBase"),
	Random = 2 UMETA(DisplayName = "RandomMovement"),
};

UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API AMSStormBase : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY()
	int32 StrengthLevel;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriggerRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte <EMSStormType> StormType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte <EMSEffect> EffectType;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bIsCharacterInStorm;

	AMSCharacter* MainCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Move")
	TEnumAsByte<EMSStormMoveType> MoveType;
	FVector MoveDirection;
	float MoveSpeed;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentEnergyLevel;
	UPROPERTY(BlueprintReadOnly)
	float CurrentEnergyTime;

	UPROPERTY(EditDefaultsOnly, Category = "Energy")
	float EnergyIncreaseFactor;

	UPROPERTY(EditDefaultsOnly, Category = "Energy")
	float EnergyDecreaseFactor;

	UPROPERTY(EditDefaultsOnly, Category = "Energy")
	TArray<float> EnergyRequiredTime;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnergyLevelChanged, int32, NewLevel);
	UPROPERTY(BlueprintAssignable)
	FOnEnergyLevelChanged OnEnergyLevelChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdatePosition(float DeltaTime);

	void UpdateEnergy(float DeltaTime);

public:	

	AMSStormBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnterStorm();

	UFUNCTION()
	virtual void AddEffectToCharacter();

	UFUNCTION()
	virtual void RemoveEffectToCharacter();

	int32 GetCurrentEnergyLevel() const { return CurrentEnergyLevel; }

	TEnumAsByte<EMSEffect> GetEffectType() const { return EffectType; }

	UFUNCTION()
	void UpdateOnPaused(bool bNewPauseState);
};
