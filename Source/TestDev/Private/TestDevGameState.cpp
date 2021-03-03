// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDevGameState.h"
#include "Net/UnrealNetwork.h"

ATestDevGameState::ATestDevGameState()
{
	PlatePlayerName = TEXT("");
}


FName ATestDevGameState::GetPlatePlayerName() const
{
	return PlatePlayerName;
}

void ATestDevGameState::SetPlatePlayerName(const FName& NewName)
{
	PlatePlayerName = NewName;
}

void ATestDevGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestDevGameState, PlatePlayerName);
}
