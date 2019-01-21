// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/TriggerVolume.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    // actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    // Find Actor
    Owner = GetOwner();
    
    if(!pressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
    }
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    if (GetTotalMassOfActorsOnPlate() >= triggerMass)
    {
        //OpenDoor();
        onOpen.Broadcast();
        doorIsOpen = true;
    }
    
    // Check if it is time to close the door
    else if (doorIsOpen == true && GetTotalMassOfActorsOnPlate() < triggerMass)
    {
        onClose.Broadcast();
        doorIsOpen = false;
    }

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float totalMass = 0.f;
    
    if(!pressurePlate) { return totalMass; } // Protection.
    
    TArray<AActor*> overlappingActors;
    
    // Find all the overlapping actors
    pressurePlate->GetOverlappingActors(OUT overlappingActors);
    
    // Iterate through them adding their masses
    for(const auto *Actor : overlappingActors)
    {
        // Log found actors
        // UE4 way of finding mass
        totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        // UE_LOG(LogTemp, Warning, TEXT("%s on the pressure plate."), Actor->GetName());
    }
    
    return totalMass;
}

