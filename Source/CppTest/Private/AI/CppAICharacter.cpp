// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"

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
    if (NewHealth <= 0.0f && Delta < 0.0f)
    {
        AAIController* AIC = Cast<AAIController>(GetController());
        if (AIC)
        {
            // Make the AI stop controlling the character
            AIC->UnPossess();
        }

        // Set a timer to destroy this actor after a delay
        // For example, 5 seconds
        SetLifeSpan(1.0f);

        // If you don't want to use SetLifeSpan, you can also use a timer:
        // GetWorld()->GetTimerManager().SetTimer(TimerHandle_DestroySelf, this, &ACppAICharacter::DestroySelf, 5.0f, false);
    }

    if (Delta < 0.0f)
    {
        GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}