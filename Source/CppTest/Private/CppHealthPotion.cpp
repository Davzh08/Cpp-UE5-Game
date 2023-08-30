// Fill out your copyright notice in the Description page of Project Settings.


#include "CppHealthPotion.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ACppHealthPotion::ACppHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionMesh");
	RootComponent = PotionMesh;

	HealValue = 50.0f;

    CooldownDuration = 10.0f;

}

void ACppHealthPotion::SpawnHealFX()
{
    if (HealEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealEffect, GetActorLocation(), GetActorRotation(), true);

        if (HealSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, HealSound, GetActorLocation());
        }
    }
}

void ACppHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
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
                SpawnHealFX();

                AttributeComp->ApplyHealthChange(HealValue);

                // 在原地生成一个特效（需要你自己设置特效）
                // UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), YourParticleEffect, GetActorLocation());

                // CD and disappear
                bIsOnCooldown = true;
                SetActorHiddenInGame(true);
                GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACppHealthPotion::ResetPotion, CooldownDuration, false);
            }
        }
    }
}

void ACppHealthPotion::ResetPotion()
{
    bIsOnCooldown = false;
    SetActorHiddenInGame(false);
}

// Called when the game starts or when spawned
void ACppHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

