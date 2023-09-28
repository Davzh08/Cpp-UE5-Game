// Fill out your copyright notice in the Description page of Project Settings.


#include "CppGameplayFunctionLibrary.h"
#include "SAttributeComponent.h"


bool UCppGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		bool bHealthChanged = AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
		bool bRageChanged = AttributeComp->ApplyRage(DamageCauser, DamageAmount);

		return bHealthChanged || bRageChanged;
	}
	return false;
}

bool UCppGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(HitResult.ImpactNormal * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}

	return false;
}