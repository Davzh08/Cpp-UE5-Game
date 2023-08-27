// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ACppTargetDummy::ACppTargetDummy()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;

    AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

    //Trigger when health is changed (Damaged/Healing)
    AttributeComp->OnHealthChanged.AddDynamic(this, &ACppTargetDummy::OnHealthChanged);

}

void ACppTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
    UE_LOG(LogTemp, Warning, TEXT("OnHealthChanged called. New Health: %f, Delta: %f"), NewHealth, Delta);
}

