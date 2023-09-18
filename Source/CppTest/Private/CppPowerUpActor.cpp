// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPowerUpActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACppPowerUpActor::ACppPowerUpActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("CreditMesh");
    ActorMesh->SetupAttachment(RootComponent);

    CooldownDuration = 10.0f;
}

void ACppPowerUpActor::SpawnFX()
{
    if (ActorEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActorEffect, GetActorLocation(), GetActorRotation(), true);

        if (ActorSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ActorSound, GetActorLocation());
        }
    }
}


void ACppPowerUpActor::ResetActor()
{
    bIsOnCooldown = false;
    SetActorHiddenInGame(false);
}