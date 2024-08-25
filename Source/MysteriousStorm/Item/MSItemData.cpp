// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemData.h"

UMSItemData::UMSItemData()
{
	ID = 0;
	XUISize = 0;
	YUISize = 0;
	RotateDegree = 0.0f;
}

void UMSItemData::RotateUI()
{
	RotateDegree += 0.25f;

	if (RotateDegree >= 1.0f)
	{
		RotateDegree = 0.0f;
	}

	int32 temp = XUISize;
	XUISize = YUISize;
	YUISize = temp;

	if (UIMaterial)
	{
		UIMaterial->SetScalarParameterValue("RotationAngle", RotateDegree);
	}
}