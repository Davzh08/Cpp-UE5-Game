// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppGamplayInterface.h"
#include "CppPowerUpActor.generated.h"

UCLASS()
class CPPTEST_API ACppPowerUpActor : public AActor, public ICppGamplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppPowerUpActor();

	UFUNCTION()
	void ResetActor();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* ActorEffect;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ActorSound;

	UFUNCTION()
	void SpawnFX();

	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	float CooldownDuration;

	FTimerHandle CooldownTimerHandle;
	bool bIsOnCooldown;
};
