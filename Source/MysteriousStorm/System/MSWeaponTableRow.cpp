// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponTableRow.h"

FMSWeaponTableRow::FMSWeaponTableRow()
{
	ItemID = 0;
	WeaponName = TEXT("None");
	SectorAngle = 0;
	SectorRadius = 0;
	WeaponType = EWeaponType::None;
	Damage = 0;
	DropDetectionRange = 0;
	DamageRange = 0;
}