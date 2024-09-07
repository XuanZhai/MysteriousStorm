// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYSTERIOUSSTORM_API WeaponUtils
{
public:
	WeaponUtils();
	~WeaponUtils();

	static float DistancePointToSegment(FVector Point, FVector Start, FVector End) ;
	static bool OverlapSectorCircle(FVector SectorCenter, FVector Forward, float Angle, float Radius, FVector CircleCenter, float CircleRadius);
	static bool OverlapCircleCircle(FVector CircleCenter1, float CircleRadius1, FVector CircleCenter2, float CircleRadius2);
	static bool OverlapRectangleCircle(FVector RectangleCenter, FVector Forward, FVector Right, FVector2f Extent, FVector CircleCenter, float CircleRadius);
};
