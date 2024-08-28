// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemActor.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/System/MSWeaponTableRow.h"
#include "MSWeaponActor.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MYSTERIOUSSTORM_API AMSWeaponActor : public AMSItemActor
{
	GENERATED_BODY()
protected:
	
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	EWeaponType WeaponType;

	FVector RuntimeOffset;
	FVector Offset;
	float RotateSpeed;
	FMSWeaponTableRow WeaponConfig;

	static float DistancePointToSegment(FVector Point, FVector Start, FVector End) ;
	static bool OverlapSectorCircle(FVector SectorCenter, FVector Forward, float Angle, float Radius, FVector CircleCenter, float CircleRadius);
	static bool OverlapCircleCircle(FVector CircleCenter1, float CircleRadius1, FVector CircleCenter2, float CircleRadius2);
	static bool OverlapRectangleCircle(FVector RectangleCenter, FVector Forward, FVector Right, float HalfWidth, float HalfHeight, FVector CircleCenter, float CircleRadius);

public:
	AMSWeaponActor();

	void SetOwnerCharacter(ACharacter* NewOwnerCharacter);
	virtual void BeginPlay() override;
	
	virtual bool TryAttack();
	bool TryReadConfig();
	virtual void Tick(float DeltaSeconds) override;
	
};
