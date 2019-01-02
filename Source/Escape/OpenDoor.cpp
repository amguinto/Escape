// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"


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
    
    actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    // Find Actor
    Owner = GetOwner();
}

void UOpenDoor::OpenDoor() {
    
    Owner->SetActorRotation(openRotation);
    doorIsOpen = true;
}

void UOpenDoor::CloseDoor() {

    Owner->SetActorRotation(closedRotation);
    doorIsOpen = false;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    if (pressurePlate->IsOverlappingActor(actorThatOpens))
    {
        OpenDoor();
        lastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    // Check if it is time to close the door
    if (doorIsOpen == true && (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay))
    {
        CloseDoor();
    }
    
}

