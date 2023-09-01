// Fill out your copyright notice in the Description page of Project Settings.


#include "CppMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
ACppMagicProjectile::ACppMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	/*SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACppMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ACppMagicProjectile::OnActorHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	FlightSoundComponent = CreateDefaultSubobject<UAudioComponent>("FlightSound");
	FlightSoundComponent->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
	DamageAmount = 20.0f;
}

void ACppMagicProjectile::SpawnExplosion()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation(), true);

		if (ExplodeSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation());
		}

		UGameplayStatics::PlayWorldCameraShake(
			this,                        // World context object
			CameraShake,                 // UCameraShakeBase subclass
			GetActorLocation(),          // Epicenter of the shake
			0.f,                         // Inner radius
			1000.f,                      // Outer radius
			1.f                          // Falloff
		);
	}
}

void ACppMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		SpawnExplosion();

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			float MagicProjectileDamage = DamageAmount;
			AttributeComp->SetDamageAmount(MagicProjectileDamage);
			AttributeComp->ApplyHealthChange(-MagicProjectileDamage);
		}

		Destroy();
	}

}

void ACppMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		SpawnExplosion();

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			float MagicProjectileDamage = DamageAmount;
			AttributeComp->SetDamageAmount(MagicProjectileDamage);
			AttributeComp->ApplyHealthChange(-MagicProjectileDamage);
		}

		Destroy();
	}
}

// Called when the game starts or when spawned
void ACppMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

