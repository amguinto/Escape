// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    void OpenDoor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // Indicates that this property is visible in property windows (In UE4), but cannot be edited at all
    // Under OpenDoor In Details
    
    UPROPERTY(VisibleAnywhere)
    float openAngle = 90.0f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume* pressurePlate;
    
    UPROPERTY(EditAnywhere)
    AActor* actorThatOpens; // Pawn inherits from Actor
};
