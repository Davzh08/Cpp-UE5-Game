// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPowerUp_HealthPotion.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "CppPlayerState.h"

// Sets default values
ACppPowerUp_HealthPotion::ACppPowerUp_HealthPotion()
{
	HealValue = 50.0f;

    CreditCost = 5;
}

void ACppPowerUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
    if (bIsOnCooldown)
    {
        return;
    }

    if (InstigatorPawn)
    {
        USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
        if (AttributeComp)
        {
            if (AttributeComp->IsAlive() && AttributeComp->GetHealth() < AttributeComp->GetHealthMax())
            {
                if (ACppPlayerState* PS = InstigatorPawn->GetPlayerState<ACppPlayerState>())
                {
                    if (PS->RemoveCredits(CreditCost))
                    {
                        SpawnFX();

                        AttributeComp->ApplyHealthChange(this, HealValue);

                        // Spawn an effect
                        // UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), YourParticleEffect, GetActorLocation());

                        // CD and disappear
                        bIsOnCooldown = true;
                        SetActorHiddenInGame(true);
                        GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACppPowerUpActor::ResetActor, CooldownDuration, false);
                    }

                }
            }
        }
    }
}