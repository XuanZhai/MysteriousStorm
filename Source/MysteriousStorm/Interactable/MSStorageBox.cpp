// Fill out your copyright notice in the Description page of Project Settings.


#include "MSStorageBox.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"

void AMSStorageBox::BeginOverlapCallback()
{
	if (auto BackpackComp = InteractingCharacter ? InteractingCharacter->GetBackpackComponent() : nullptr)
	{
		BackpackComp->InteractingStorageBox = this;
		if (BackpackComp->OnEnterStorageBox.IsBound())
		{
			BackpackComp->OnEnterStorageBox.Broadcast(this);
		}
	}
}

void AMSStorageBox::EndOverlapCallback()
{
	if (auto BackpackComp = InteractingCharacter ? InteractingCharacter->GetBackpackComponent() : nullptr)
	{
		if (BackpackComp->OnLeaveStorageBox.IsBound())
		{
			BackpackComp->OnLeaveStorageBox.Broadcast(this);
		}
		BackpackComp->InteractingStorageBox = nullptr;
	}
}