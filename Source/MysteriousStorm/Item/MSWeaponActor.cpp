// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponActor.h"

#include "MysteriousStorm/System/MSDataTableSubsystem.h"


AMSWeaponActor::AMSWeaponActor()
{
	//TryReadConfig();
}

void AMSWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	TryReadConfig();

	Offset = FVector(100, 0, 0);
	RuntimeOffset = Offset.RotateAngleAxis(FMath::FRandRange(0.0f, 100.0f), FVector(0, 0, 1));
	RotateSpeed = 200;
	
}


void AMSWeaponActor::SetOwnerCharacter(ACharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;
	SetActorLocation(OwnerCharacter->GetActorLocation() + Offset);
}

bool AMSWeaponActor::TryAttack()
{
	return true;
}

bool AMSWeaponActor::TryReadConfig()
{
	UGameInstance* GameInstance = GetGameInstance();
	GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetWeaponConfigByItemID(ItemID,WeaponConfig);
	return true;
}

void AMSWeaponActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// 基于上一帧的runtimeoffset,将这一帧的旋转施加到actor上

	RuntimeOffset = RuntimeOffset.RotateAngleAxis(RotateSpeed * DeltaSeconds, FVector(0, 0, 1));
	SetActorLocation(OwnerCharacter->GetActorLocation() + RuntimeOffset);
}


#pragma region collsion
// 默认所有的检测都是2D的，因此只需考虑yaw
float AMSWeaponActor::DistancePointToSegment(const FVector& Point, const FVector& Start, const FVector& End)
{
	// 计算point到线段的距离
	FVector Segment = End - Start;
	FVector PointToStart = Point - Start;
	FVector PointToEnd = Point - End;

	float SegmentLength = Segment.Size();
	float Distance = FVector::CrossProduct(Segment, PointToStart).Size() / SegmentLength;
	float Projection = FVector::DotProduct(Segment, PointToStart) / SegmentLength;

	if (Projection < 0)
	{
		Distance = PointToStart.Size();
	}
	else if (Projection > SegmentLength)
	{
		Distance = PointToEnd.Size();
	}

	return Distance;
}

bool AMSWeaponActor::OverlapSectorCircle(const FVector& SectorCenter, FVector Forward, float Angle, float Radius,
                                         const FVector& CircleCenter, float CircleRadius)
{
	float CenterDistance = FVector::Dist(SectorCenter, CircleCenter);
	if (CenterDistance > (Radius+CircleRadius))
	{
		return false;
	}

	if (DistancePointToSegment(CircleCenter, SectorCenter,
	                           SectorCenter + Forward.RotateAngleAxis(-Angle / 2, FVector::UpVector) * Radius) > CircleRadius
		||
		DistancePointToSegment(CircleCenter, SectorCenter,
		                       SectorCenter + Forward.RotateAngleAxis(Angle / 2, FVector::UpVector) * Radius) > CircleRadius)
	{
		return false;
	}

	return true;
}
# pragma endregion
