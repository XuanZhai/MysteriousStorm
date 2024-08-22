// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MSCharacter.generated.h"

class UMSBackpackComponent;

UCLASS()
class MYSTERIOUSSTORM_API AMSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMSBackpackComponent* BackpackComponent;

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
};
