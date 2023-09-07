// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "BrainComponent.h"

// Sets default values
ACppAICharacter::ACppAICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}


void ACppAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ACppAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &ACppAICharacter::OnHealthChanged);
}

void ACppAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

void ACppAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        if (NewHealth <= 0.0f)
        {
            //Stop BT
            AAIController* AIC = Cast<AAIController>(GetController());
            if (AIC)
            {
                // Make the AI stop controlling the character
                AIC->GetBrainComponent()->StopLogic("Killed");
            }

            //Ragdoll
            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName("Ragdoll");

            // Set a timer to destroy this actor after a del. Life Span
            SetLifeSpan(10.0f);
        }
    }

    if (Delta < 0.0f)
    {
        GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}