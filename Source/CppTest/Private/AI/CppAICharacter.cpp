// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CppAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "BrainComponent.h"
#include "CppWorldUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SActionComponent.h"

// Sets default values
ACppAICharacter::ACppAICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

    ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(true);
}


void ACppAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ACppAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &ACppAICharacter::OnHealthChanged);
}

void ACppAICharacter::OnPawnSeen(APawn* Pawn)
{
    SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ACppAICharacter::SetTargetActor(AActor* NewTarget)
{
    AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC)
    {
        AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
    }
}

void ACppAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        if (InstigatorActor != this)
        {
            SetTargetActor(InstigatorActor);
        }


        if (ActiveHealthBar == nullptr)
        {
            ActiveHealthBar = CreateWidget<UCppWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
            if (ActiveHealthBar)
            {
                ActiveHealthBar->AttachedActor = this;
                ActiveHealthBar->AddToViewport();
            }
        }


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

            GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            GetCharacterMovement()->DisableMovement();

            // Set a timer to destroy this actor after a del. Life Span
            SetLifeSpan(10.0f);
        }
    }

    if (Delta < 0.0f)
    {
        GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}

void ACppAICharacter::HealToFull()
{
    AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax());
}