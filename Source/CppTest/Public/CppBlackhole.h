// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppProjectileBase.h"
#include "CppBlackhole.generated.h"

class URadialForceComponent;
class UProjectileMovementComponent;

UCLASS()
class CPPTEST_API ACppBlackhole : public ACppProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACppBlackhole();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* ForceComp;

	UPROPERTY()
	FTimerHandle DestroyTimer;

	virtual void BeginPlay() override;

	void DestroyBlackhole();

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};