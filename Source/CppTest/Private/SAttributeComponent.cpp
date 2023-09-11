// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "CppGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
    HealthMax = 100;
    Health = HealthMax;
    DamageAmount = 20.0f;
}

void USAttributeComponent::SetDamageAmount(float NewDamageAmount)
{
    DamageAmount = NewDamageAmount;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float NewDamageAmount)
{
    if (NewDamageAmount < 0.0f)
    {
        float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

        NewDamageAmount *= DamageMultiplier;
    }


    // record health before health change
    float OldHealth = Health;

    // apply health change
    Health = FMath::Clamp(Health + NewDamageAmount, 0.0f, HealthMax);

    float ActualDamage = Health - OldHealth;

    // check if health really changed
    if (OldHealth != Health)
    {
        OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDamage);
    }

    //Died
    if (ActualDamage < 0.0f && Health == 0.0f)
    {
        ACppGameModeBase* GM = GetWorld()->GetAuthGameMode<ACppGameModeBase>();
        if (GM)
        {
            GM->OnActorKilled(GetOwner(), InstigatorActor);
        }
    }

    return ActualDamage != 0;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
    if (FromActor)
    {
        return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
    }

    return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
    USAttributeComponent* AttributeComp = GetAttributes(Actor);
    if (AttributeComp)
    {
        return AttributeComp->IsAlive();
    }

    return false;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
    return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}