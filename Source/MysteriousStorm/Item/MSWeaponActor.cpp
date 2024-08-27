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
	GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetWeaponConfigByItemID(ItemID, WeaponConfig);
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
#pragma optimize("", off)
// 默认所有的检测都是2D的，因此只需考虑yaw
float AMSWeaponActor::DistancePointToSegment(FVector Point, FVector Start, FVector End)
{
	End.Z = 0;
	Point.Z = 0;
	Start.Z = 0;
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

bool AMSWeaponActor::OverlapSectorCircle(FVector SectorCenter, FVector Forward, float Angle, float Radius, FVector CircleCenter, float CircleRadius)
{
	SectorCenter.Z = 0;
	Forward.Z = 0;
	Forward.Normalize();
	CircleCenter.Z = 0;
	float CenterDistance = FVector::Dist(SectorCenter, CircleCenter);
	if (CenterDistance > (Radius + CircleRadius))
	{
		return false;
	}
	auto Offset = CircleCenter - SectorCenter;
	Offset.Normalize();
	if (Forward.Dot(Offset) > FMath::Cos(Angle / 2))
	{
		return true;
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

bool AMSWeaponActor::OverlapCircleCircle(FVector CircleCenter1, float CircleRadius1, FVector CircleCenter2, float CircleRadius2)
{
	CircleCenter1.Z = 0;
	CircleCenter2.Z = 0;
	return FVector::Dist(CircleCenter1, CircleCenter2) <= CircleRadius1 + CircleRadius2;
}
#pragma optimize("", on)
# pragma endregion
