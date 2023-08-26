// Fill out your copyright notice in the Description page of Project Settings.


#include "CppDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemCOmponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACppDashProjectile::ACppDashProjectile()
{
    TeleportDelay = 0.2f;
    DetonateDelay = 0.2f;

    MoveComp->InitialSpeed = 6000.0f;

}

void ACppDashProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ACppDashProjectile::Explode, DetonateDelay);
}

void ACppDashProjectile::Explode_Implementation()
{
   
    //Clear timer if the Explode was already called through another source like OnActorHit
    GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

    UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

    EffectComp->DeactivateSystem();

    MoveComp->StopMovementImmediately();
    SetActorEnableCollision(false);

    FTimerHandle TimerHandle_DelayedTeleport;
    GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ACppDashProjectile::TeleportInstigator, TeleportDelay);

    //Skip base implementation as it will destroy actor
}

void ACppDashProjectile::TeleportInstigator()
{
    AActor* ActorToTeleport = GetInstigator();
    if (ensure(ActorToTeleport))
    {
        //Keep Instigator rotation or it may end up jarring
        ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
    }

}