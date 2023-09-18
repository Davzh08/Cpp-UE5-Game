// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppPowerUpActor.h"
#include "CppPowerUp_Credits.generated.h"

UCLASS()
class CPPTEST_API ACppPowerUp_Credits : public ACppPowerUpActor
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ACppPowerUp_Credits();

protected:

	UPROPERTY()
	int32 CreditsAmount;
};
