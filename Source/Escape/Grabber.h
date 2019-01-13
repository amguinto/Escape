// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
    // How far ahead of the player we can reach in cm
    float reach = 100.0f;
    
    // Player position and line of sight
    FVector playerViewPointLocation;
    FRotator playerViewPointRotation;
    FVector lineTraceEnd;
		
	// Ray Cast Variables
    FHitResult hit;
    
    // Physics Handler in DefaultPawn_BP
    UPhysicsHandleComponent* physicsHandle = nullptr;
    
    UInputComponent* inputComponent = nullptr;
    
    // Ray-cast and grab what is in reach
    void Grab();
};
