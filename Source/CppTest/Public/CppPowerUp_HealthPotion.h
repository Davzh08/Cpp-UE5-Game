// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppPowerUpActor.h"
#include "CppPowerUp_HealthPotion.generated.h"

UCLASS()
class CPPTEST_API ACppPowerUp_HealthPotion : public ACppPowerUpActor
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal")
	float HealValue;

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditCost;

public:	
	
	// Sets default values for this actor's properties
	ACppPowerUp_HealthPotion();
};
