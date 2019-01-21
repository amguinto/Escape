// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Gameframework/Actor.h"
#include "OpenDoor.generated.h"

// Used to declare BluePrint in C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


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
    
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    // Blueprint Variable
    UPROPERTY(BlueprintAssignable)
    FDoorEvent onOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent onClose;
    
private:
    // Indicates that this property is visible in property windows (In UE4), but cannot be edited at all
    // Under OpenDoor In Details

    UPROPERTY(EditAnywhere)
    ATriggerVolume* pressurePlate = nullptr;
    
    UPROPERTY(VisibleAnywhere)
    AActor* actorThatOpens = nullptr; // Pawn inherits from Actor
    
    AActor* Owner = nullptr; // The Owning Door
    
    bool doorIsOpen;
    
    FRotator openRotation = FRotator(0.0f, 90.0f, 0.0f);
    FRotator closedRotation = FRotator(0.0f, -90.0f, 0.0f);
    
    // Returns total mass in kg
    float GetTotalMassOfActorsOnPlate();
    
    UPROPERTY(EditAnywhere)
    float triggerMass = 20.f;
};
