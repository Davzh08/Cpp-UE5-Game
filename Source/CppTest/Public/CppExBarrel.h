// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppExBarrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class CPPTEST_API ACppExBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppExBarrel();

	//Function to explode the barrel by using Explode Lever
	UFUNCTION()
	void Explode(); 

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;
	
	virtual void PostInitializeComponents() override;

	//Must be marked with ufunction in order to 'bind' the event
	

};
