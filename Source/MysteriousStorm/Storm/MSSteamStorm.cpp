// Fill out your copyright notice in the Description page of Project Settings.


#include "MSSteamStorm.h"

AMSSteamStorm::AMSSteamStorm()
{
	StormType = EMSStormType::SteamStorm;

	SteamSelfDamageFactor = 1.0f;
	SteamHitDamageFactor = 1.0f;
}