// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSAttributeComponent.h"
#include "MSWeaponComponent.h"
#include "GameFramework/Character.h"
#include "MSCharacter.generated.h"

class UMSBackpackComponent;

UENUM(BlueprintType)
enum EMSEffect : uint32
{
	None = 0,
	Steam = 1,
};


UCLASS()
class MYSTERIOUSSTORM_API AMSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMSBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMSWeaponComponent* WeaponComponent;

	UPROPERTY()
	UMSAttributeComponent* AttributeComponent;

public:
	// Sets default values for this character's properties
	AMSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UMSBackpackComponent* GetBackpackComponent() const { return BackpackComponent;  }


#pragma region Storm

protected:
	uint8 StormState;

public:
	void AddStorm(uint8 StormID);

	void RemoveStorm(uint8 StormID);

#pragma endregion
};
