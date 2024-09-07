// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUtils.h"

WeaponUtils::WeaponUtils()
{
}

WeaponUtils::~WeaponUtils()
{
}

// 默认所有的检测都是2D的，因此只需考虑yaw
float WeaponUtils::DistancePointToSegment(FVector Point, FVector Start, FVector End)
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

bool WeaponUtils::OverlapSectorCircle(FVector SectorCenter, FVector Forward, float Angle, float Radius,
                                         FVector CircleCenter, float CircleRadius)
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
	                           SectorCenter + Forward.RotateAngleAxis(-Angle / 2, FVector::UpVector) * Radius) >
		CircleRadius
		||
		DistancePointToSegment(CircleCenter, SectorCenter,
		                       SectorCenter + Forward.RotateAngleAxis(Angle / 2, FVector::UpVector) * Radius) >
		CircleRadius)
	{
		return false;
	}

	return true;
}

bool WeaponUtils::OverlapCircleCircle(FVector CircleCenter1, float CircleRadius1, FVector CircleCenter2,
                                         float CircleRadius2)
{
	CircleCenter1.Z = 0;
	CircleCenter2.Z = 0;
	return FVector::Dist(CircleCenter1, CircleCenter2) <= CircleRadius1 + CircleRadius2;
}

// TODO：rectangle vs circle
bool WeaponUtils::OverlapRectangleCircle(FVector RectangleCenter, FVector Forward, FVector Right, FVector2f Extent,
                                            FVector CircleCenter, float CircleRadius)
{
	// 将圆心投影到矩形的坐标系下再计算距离
	RectangleCenter.Z = 0;
	CircleCenter.Z = 0;
	FVector Offset = CircleCenter - RectangleCenter;

	Forward.Normalize();
	Right.Normalize();
	FVector ProjectedOffset = FVector::DotProduct(Offset, Forward) * Forward + FVector::DotProduct(Offset, Right) *
		Right;
	if (ProjectedOffset.X > (Extent.X + CircleRadius) || ProjectedOffset.Y > (Extent.Y + CircleRadius))
	{
		return false;
	}
	return true;
}