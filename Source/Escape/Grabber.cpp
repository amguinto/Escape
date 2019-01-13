// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
    
    // Look for attached Physics Handle
    physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (physicsHandle)
    {
        // Physics handle is found
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }
    
    // Look for attached Input Component (only appears at runtime)
    inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (inputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input Component found"), *GetOwner()->GetName());
        
        // Bind the input action
        inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        
        // Pressing the Grab button again will release
        inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
    }
	
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"), *GetOwner()->GetName());

}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Released"), *GetOwner()->GetName());

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotation);
    
    // Log Viewpoint every tick
    // UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());

    lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;
    
    // Draw a red trace in the world for visual purposes
    DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 10.0f);
    
    
    // Set up query parameters
    FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
    
    // Ray-cast out to reach distance
    GetWorld()->LineTraceSingleByObjectType(OUT hit, playerViewPointLocation, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParameters);
    
    // See what we hit
    AActor* actorHit = hit.GetActor();
    
    // Must be a physics object
    if(actorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit)->GetName());

    }
}

