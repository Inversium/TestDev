// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlateEntered)
DECLARE_MULTICAST_DELEGATE(FOnPlateLeaved)

UCLASS(Blueprintable)
class TESTDEV_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* PlateMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent* PlateCollision;
	
	
	FOnPlateEntered OnPlateEntered;
	FOnPlateLeaved OnPlateLeaved;

private:

	UPROPERTY()
	bool bPlateMoving;

	UPROPERTY()
	bool bStepped;

	UPROPERTY()
	FVector NormalPlateLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnTriggerEntered(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerLeaved(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	

};
