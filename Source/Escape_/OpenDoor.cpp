// Francisco Viramontes 2020

#include "OpenDoor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Getting object details
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (GetTotalMassOnPlate() > TriggerMass)
	{
		OpeningDoor();
	}
	else
	{
		ClosingDoor();
	}
}

void UOpenDoor::OpeningDoor()
{
	OnOpenRequest.Broadcast();
}

void UOpenDoor::ClosingDoor()
{
	OnCloseRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOnPlate() 
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;

	//Updates Overlapping Actors
	PressurePlate->GetOverlappingActors(OverlappingActors);

	
	for (const auto* Actor : OverlappingActors)
	{
		UPrimitiveComponent* OverlappedActor = Actor->FindComponentByClass<UPrimitiveComponent>();
		if (OverlappedActor)
		{
			TotalMass += OverlappedActor->GetMass();
		}
	}

	return TotalMass;
}