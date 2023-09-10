// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppBTService_CheckLowHealth.h"
#include "AI/CppAICharacter.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UCppBTService_CheckLowHealth::UCppBTService_CheckLowHealth()
{
	bNotifyTick = true;
	Interval = 0.5f;  // Every 0.5 seconds
	RandomDeviation = 0.1f; // +- 0.1 seconds
}

void UCppBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn);
		if (ensure(AttributeComp))
		{
			bool bIsLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetHealthMax()) <= HealthThreshold;

			UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
			BlackBoardComp->SetValueAsBool(IsLowHealthKey.SelectedKeyName, bIsLowHealth);
		}
	}
}
