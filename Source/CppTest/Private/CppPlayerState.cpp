// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayerState.h"


void ACppPlayerState::AddCredits(int32 Delta)
{
	//avoid negative amount
	if (!ensure(Delta > 0.0f))
	{
		return;
	}

	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ACppPlayerState::RemoveCredits(int32 Delta)
{
	//avoid negative amount 
	if (!ensure(Delta > 0.0f))
	{
		return false;
	}

	//not enough credits
	if (Credits < Delta)
	{
		return false;
	}

	Credits -= Delta;

	OnCreditsChanged.Broadcast(this, Credits, -Delta);

	return true;
}

int32 ACppPlayerState::GetCredits() const
{
	return Credits;
}