// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPowerUp_Credits.h"
#include "CppPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACppPowerUp_Credits::ACppPowerUp_Credits()
{
    CreditsAmount = 10;
}


void ACppPowerUp_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
    if (InstigatorPawn)
    {
        if (ACppPlayerState* PS = InstigatorPawn->GetPlayerState<ACppPlayerState>())
        {
            PS->AddCredits(CreditsAmount);

            SpawnFX();

            bIsOnCooldown = true;
            SetActorHiddenInGame(true);
            GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACppPowerUpActor::ResetActor, CooldownDuration, false);
        }
    }
}