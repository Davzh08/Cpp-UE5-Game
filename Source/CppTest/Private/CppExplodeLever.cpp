// Fill out your copyright notice in the Description page of Project Settings.


#include "CppExplodeLever.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACppExplodeLever::ACppExplodeLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetupAttachment(BaseMesh);

	TargetPitch = -30;
}

void ACppExplodeLever::Interact_Implementation(APawn* InstigatorPawn)
{
	HandleMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));

	// Let the barrel explode
	for (ACppExBarrel* Barrel : ExplodingBarrels)
	{
		if (Barrel)
		{
			Barrel->Explode(); // explode definition in CppExBarrel
		}
	}
}

// Called when the game starts or when spawned
void ACppExplodeLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppExplodeLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

