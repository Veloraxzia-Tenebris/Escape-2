// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	//Grabs the object's name (e.g. chair, rock, door)
	FString ObjectName = GetOwner()->GetName();

	//Gets the X-Y-Z coordinates in vector format and converts to a string
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();

	//Logs object name and object position to the Output Log
	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

