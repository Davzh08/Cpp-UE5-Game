// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppGamplayInterface.h"
#include "CppExBarrel.h"
#include "CppExplodeLever.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPPTEST_API ACppExplodeLever : public AActor, public ICppGamplayInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere, Category = "Barrels")
	TArray<ACppExBarrel*> ExplodingBarrels; // the array that save the barrel you want to explode by lever

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HandleMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	ACppExplodeLever();
};
