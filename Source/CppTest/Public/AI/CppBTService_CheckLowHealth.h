// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CppBTService_CheckLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class CPPTEST_API UCppBTService_CheckLowHealth : public UBTService
{
	GENERATED_BODY()
	
public:
	UCppBTService_CheckLowHealth();

protected:
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsLowHealthKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthThreshold = 0.3f; //30% or any other value you consider as low health


};
