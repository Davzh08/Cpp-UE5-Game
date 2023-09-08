// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTEST_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthMax() const { return HealthMax; }
	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	//EditAnywhere - edit in BP editor and per-instance in level
	//VisibleAnywhere - 'read-only' in editor and level. (Use for Components)
	//EditDefaultsOnly - hide variable per-instance, edit in BP editor only
	//VisibleDefaultsOnly - 'read-only' access for variable, only in BP editor (uncommon)
	//EditInstanceOnly - allow only editing of instance (eg. when placed in level)
	//--
	//BlueprintReadOnly - read-only in the Blueprint scripting (does not affect 'details' panel)
	//BlueprintReadWrite - read-write access in Blueprints
	//--
	//Category = "" - display only for detail panels and blueprint context menu

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float DamageAmount;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float NewDamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetDamageAmount(float NewDamageAmount);
	
};
