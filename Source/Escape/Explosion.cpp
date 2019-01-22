// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosion.h"


// Sets default values for this component's properties
UExplosion::UExplosion()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExplosion::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExplosion::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Poll the Trigger Volume
    if (GetTotalMassOfActorsOnPlate() >= triggerMass)
    {
        //OpenDoor();
        onExplode.Broadcast();
    }
}

float UExplosion::GetTotalMassOfActorsOnPlate()
{
    float totalMass = 0.f;
    
    if(!explosionTrigger) { return totalMass; } // Protection.
    
    TArray<AActor*> overlappingActors;
    
    // Find all the overlapping actors
    explosionTrigger->GetOverlappingActors(OUT overlappingActors);
    
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

