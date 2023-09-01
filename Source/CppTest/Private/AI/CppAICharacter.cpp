// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppAICharacter.h"

// Sets default values
ACppAICharacter::ACppAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACppAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACppAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

