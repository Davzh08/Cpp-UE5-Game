// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppBTTask_HealSelf.h"
#include "AIController.h"
#include "AI/CppAICharacter.h"

UCppBTTask_HealSelf::UCppBTTask_HealSelf()
{
    NodeName = "Heal Self to Full";
}


EBTNodeResult::Type UCppBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    ACppAICharacter* AICharacter = Cast<ACppAICharacter>(AIController->GetPawn());
    if (!AICharacter)
    {
        return EBTNodeResult::Failed;
    }

    // Heal the AI to full health
    AICharacter->HealToFull();

    return EBTNodeResult::Succeeded;
}



