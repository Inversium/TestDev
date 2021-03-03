// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestDevGameState.generated.h"

/**
 * 
 */
UCLASS()
class TESTDEV_API ATestDevGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY(Replicated)
	FName PlatePlayerName;
public:
	ATestDevGameState();

public:
	FName GetPlatePlayerName() const;
	void SetPlatePlayerName(const FName& NewName);
	
};
