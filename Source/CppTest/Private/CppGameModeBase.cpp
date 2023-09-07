// Fill out your copyright notice in the Description page of Project Settings. 


#include "CppGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/CppAICharacter.h"
#include "SAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"




ACppGameModeBase::ACppGameModeBase()
{
	SpawnTimerInterval = 5.0f;
}


void ACppGameModeBase::StartPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("StartPlay has been called!"));
	
	Super::StartPlay();

	//Continuous timer to spawn in more bots
	//Actual amount of bots and whether its allowed to spawn determined by spawn logic later in the chain
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ACppGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ACppGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ACppGameModeBase::OnQueryCompleted);
	}
}

void ACppGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	UE_LOG(LogTemp, Warning, TEXT("OnQueryCompleted has been called! Status: %d"), (int32)QueryStatus);
	
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"));
		return;
	}
	
	int32 NrOfAliveBots = 0;
	for (TActorIterator<ACppAICharacter> It(GetWorld()); It; ++It)
	{
		ACppAICharacter* Bot = *It;

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Number of Alive Bots: %d"), NrOfAliveBots);
	
	float MaxBotCount = 10.0f;
	
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	
	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity, skipping bot spawn."))
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawn Location: %s"), *Locations[0].ToString());
}




