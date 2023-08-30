// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBlackhole.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACppBlackhole::ACppBlackhole()
{
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);

	// Activate the force component so it constantly applies forces
	ForceComp->SetAutoActivate(true);

	ForceComp->Radius = 750.0f;

	// Use ForceStrength instead of ImpulseStrength for a continuous force
	ForceComp->ForceStrength = -200000.0f;  // A negative value creates a pulling force

	// Disable impulse since we're using a continuous force
	ForceComp->bImpulseVelChange = false;
	ForceComp->bIgnoreOwningActor = true;  // So it doesn't affect the blackhole itself
}

void ACppBlackhole::BeginPlay()
{
	Super::BeginPlay();

	// Set timer to destroy blackhole, the time that blackhole last
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ACppBlackhole::DestroyBlackhole, 5.2f, false);

	// Set timer to apply camera shake periodically
	GetWorldTimerManager().SetTimer(CameraShakeTimer, this, &ACppBlackhole::ApplyCameraShake, 0.2f, true);

}

void ACppBlackhole::DestroyBlackhole()
{
	Destroy();
}

void ACppBlackhole::ApplyCameraShake()
{
	UGameplayStatics::PlayWorldCameraShake(
		this,                        // World context object
		CameraShake,                 // UCameraShakeBase subclass
		GetActorLocation(),          // Epicenter of the shake
		0.f,                         // Inner radius
		2000.f,                      // Outer radius
		1.f                          // Falloff
	);
}

