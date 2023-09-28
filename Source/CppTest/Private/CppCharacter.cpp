// Fill out your copyright notice in the Description page of Project Settings.


#include "CppCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CppInteractionComponent.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACppCharacter::ACppCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UCppInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	BlackholeRageCost = 100;
}

void ACppCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ACppCharacter::OnHealthChanged);
}

FVector ACppCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called to bind functionality to input
void ACppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACppCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACppCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACppCharacter::MoveRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACppCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACppCharacter::SprintStop);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Up", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ACppCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Blackhole", IE_Pressed, this, &ACppCharacter::Blackhole);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACppCharacter::Dash);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ACppCharacter::PrimaryInteract);
}

void ACppCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ACppCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	//X = Forward (Red)
	//Y = Right (Green)
	//Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, value);
}

void ACppCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ACppCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


void ACppCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void ACppCharacter::Dash()
{
	ActionComp->StartActionByName(this, "Dash");
}

void ACppCharacter::Blackhole()
{
	if (AttributeComp && AttributeComp->GetRage() >= BlackholeRageCost)
	{
		AttributeComp->ApplyRage(this, -BlackholeRageCost);

		ActionComp->StartActionByName(this, "Blackhole");
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, InsufficientSound, GetActorLocation());
	}
}

void ACppCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ACppCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}

	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

void ACppCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}