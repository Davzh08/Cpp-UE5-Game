// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CppCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCppInteractionComponent;
class UAnimMontage;

UCLASS()
class CPPTEST_API ACppCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Dash")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Dash")
	UAnimMontage* DashAnim;

	UPROPERTY(EditAnywhere, Category = "Blackhole")
	TSubclassOf<AActor> BlackholeProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Blackhole")
	UAnimMontage* BlackholeAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

	FTimerHandle TimerHandle_Dash;

	FTimerHandle TimerHandle_Blackhole;

public:
	// Sets default values for this character's properties
	ACppCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UCppInteractionComponent* InteractionComp;

	void MoveForward(float value);
	
	void MoveRight(float value);

	void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();

	void Dash();

	void Dash_TimeElapsed();

	void Blackhole();

	void Blackhole_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> classToSpawn);

	void PrimaryInteract();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
