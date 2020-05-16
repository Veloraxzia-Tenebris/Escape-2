// Francisco Viramontes 2020

#include "Grabber.h"
#include "Engine/World.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Looks for physics handle
	FindPhysicsComponent();
	//Looks for input handle
	FindInputComponent();
}

void UGrabber::FindPhysicsComponent()
{
	//Looks for PhysicsHandleComponent objects in the game
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Gimmie"));
		}
	}
	else
	{
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Cannot grab 1"));
		}
	}
}

void UGrabber::FindInputComponent()
{
	//Lets the player grab grabable object with LMB and LShift
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Cannot grab 2"));
		}
	}
}

void UGrabber::Grab()
{
	//Change false to true to visualize grabbing objects
	bool bDebug = true;
	FHitResult HitResult = GetPhysicsBodyInReach(bDebug);
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	//If Player is in reach and there is an object to grab within its reach
	if ( (ActorHit) && (ComponentToGrab) )
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, 
			NAME_None, 
			ComponentToGrab->GetOwner()->GetActorLocation(), 
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool bLineTraceDebug = false;

	if (PhysicsHandle)
	{
		if (PhysicsHandle->GrabbedComponent)
		{
			FVector PlayerLineTraceEnd = GetLineTracePoints(bLineTraceDebug).v2;
			PhysicsHandle->SetTargetLocation(PlayerLineTraceEnd);
		}
	}
}

//Checks if there is an physics body in reach of the player
const FHitResult UGrabber::GetPhysicsBodyInReach(bool bDebug=false)
{
	FTwoVectors PlayerViewLocationAndLineTraceEnd = GetLineTracePoints(bDebug);

	FVector PlayerViewPointLocation = PlayerViewLocationAndLineTraceEnd.v1;
	FVector PlayerLineTraceEnd = PlayerViewLocationAndLineTraceEnd.v2;

	if (bDebug)
	{
		//Creates a line trace end and shows it as a red line in the game world
		DrawDebugLine(
			GetWorld(),
			PlayerViewPointLocation,
			PlayerLineTraceEnd,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.0f,
			10.0f
		);
	}

	//Set up query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("Nothing")), false, GetOwner());

	//Ray-cast out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		PlayerViewPointLocation,
		PlayerLineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//Logs if there is a successful grab
	if (bDebug)
	{
		//See what we hit
		AActor* ActorHit = LineTraceHit.GetActor();
		if (ActorHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
		}
	}

	return LineTraceHit;
}

FTwoVectors UGrabber::GetLineTracePoints(bool bDebug) const
{
	//x, y, z
	FVector PlayerViewPointLocation;

	//pitch (p), yaw (y), roll (r)
	FRotator PlayerViewPointRotation;

	//Update Location and rotation of the player and wrtie to PlayerViewPointLocation, and PlayerViewPointRotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//Logs player location and rotation
	if (bDebug)
	{
		//Convert data to strings
		FString PlayerViewLocationString = PlayerViewPointLocation.ToString();
		FString PlayerViewRotationString = PlayerViewPointRotation.ToString();

		//Print string to log, used for debugging purposes
		UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewLocationString, *PlayerViewRotationString);
	}

	FVector PlayerLineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	return FTwoVectors(PlayerViewPointLocation, PlayerLineTraceEnd);
}