// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape_GameModeBase.h"



void AEscape_GameModeBase::StartPlay() {

	Super::StartPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, TEXT("World loads good"));
	}
}