// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponActor.h"

AMSWeaponActor::AMSWeaponActor()
{
	StaticMeshComp = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	
}