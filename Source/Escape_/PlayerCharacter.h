// Sonny Ji 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ESCAPE__API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Moves forwards and backwards
	UFUNCTION()
	void UpDown(float Value);

	// Moves left and right
	UFUNCTION()
	void LeftRight(float Value);

	// Does jumping stuff
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();
	
	
};
