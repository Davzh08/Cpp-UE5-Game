// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppGamplayInterface.h"
#include "CppHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPPTEST_API ACppHealthPotion : public AActor, public ICppGamplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal")
	float HealValue;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PotionMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	float CooldownDuration;

	UPROPERTY(EditDefaultsOnly, Category = "HealEffect")
	UParticleSystem* HealEffect;

	UPROPERTY(EditAnywhere, Category = "HealSound")
	USoundBase* HealSound;

	FTimerHandle CooldownTimerHandle;
	bool bIsOnCooldown;

	UFUNCTION()
	void SpawnHealFX();

public:	
	UFUNCTION()
	void ResetPotion();
	
	// Sets default values for this actor's properties
	ACppHealthPotion();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
