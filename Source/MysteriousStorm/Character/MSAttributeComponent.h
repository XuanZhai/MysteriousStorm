// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MSAttributeComponent.generated.h"

UENUM(BlueprintType)
enum EMSEffect : uint8
{
	None = 0,
	SteamStormEffect = 1 UMETA(DisplayName = "SteamStorm"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERIOUSSTORM_API UMSAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMSAttributeComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute")
	float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute")
	float InvincibleTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute")
	float MoveSpeed;
	
	UPROPERTY(BlueprintReadWrite)
	TSet<TEnumAsByte<EMSEffect>> Effects;

protected:

	float currentHealth;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


#pragma region Effect

	void AddEffect(EMSEffect NewEffect);

	void RemoveEffect(EMSEffect TargetEffect);

#pragma endregion
};
