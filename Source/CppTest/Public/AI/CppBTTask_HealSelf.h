// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CppBTTask_HealSelf.generated.h"

/**
 * 
 */
UCLASS()
class CPPTEST_API UCppBTTask_HealSelf : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UCppBTTask_HealSelf();

};
