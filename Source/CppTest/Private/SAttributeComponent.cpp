// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

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
    // record health before health change
    float OldHealth = Health;

    // apply health change
    Health = FMath::Clamp(Health + NewDamageAmount, 0.0f, HealthMax);

    // check if health really changed
    if (OldHealth != Health)
    {
        OnHealthChanged.Broadcast(InstigatorActor, this, Health, Health - OldHealth);
    }

    return true;
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