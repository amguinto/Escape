// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Explosion.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExplosion);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UExplosion : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExplosion();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UPROPERTY(BlueprintAssignable)
    FExplosion onExplode;
    
private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* explosionTrigger = nullptr;
	
    // Returns total mass in kg
    float GetTotalMassOfActorsOnPlate();
    float triggerMass = 20.f;
};
