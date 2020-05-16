// Sonny Ji 2020

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// To check if player loads right
	if(GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Oop, we here, we livin'"));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement stuff
	PlayerInputComponent->BindAxis("UpDown", this, &APlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis("LeftRight", this, &APlayerCharacter::LeftRight);

	// Looking stuff
	PlayerInputComponent->BindAxis("LookLR", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUD", this, &APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
}


// Make movement changes relative to camera
void APlayerCharacter::UpDown(float V) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, V);
}

void APlayerCharacter::LeftRight(float V) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, V);
}

// Toggles "jump"ness
void APlayerCharacter::StartJump() {
	bPressedJump = true;
}
void APlayerCharacter::StopJump() {
	bPressedJump = false;
}