// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

UCLASS()
class TESTDEV_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALamp();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* LampMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UPointLightComponent* LampLight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class APressurePlate* TriggerPlate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION(NetMulticast, Reliable)
	void OnTriggerActivated();

	UFUNCTION(NetMulticast, Reliable)
	void OnTriggerDisactivated();

};
