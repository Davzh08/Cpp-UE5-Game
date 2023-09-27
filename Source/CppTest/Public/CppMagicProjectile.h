// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "CppProjectileBase.h"
#include "SAction_Effect.h"
#include "CppMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class CPPTEST_API ACppMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACppMagicProjectile();

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SpawnExplosion();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "ExplosionEffect")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlightSound")
	UAudioComponent* FlightSoundComponent;

	UPROPERTY(EditAnywhere, Category = "ExplodeSound")
	USoundBase* ExplodeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Amount")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Damage Amount")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage Amount")
	TSubclassOf<USAction_Effect> BurningActionClass;
};
