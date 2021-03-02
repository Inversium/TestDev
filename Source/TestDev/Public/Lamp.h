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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UStaticMeshComponent* LampMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UPointLightComponent* LampLight;
	
	/* Reference to Plate in the level */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lamp")
	class APressurePlate* TriggerPlate;

	/* Initial Lamp Color */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lamp")
	FLinearColor InitialColor;

	/* Speed at which lamp color changes (percents per second) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp")
	float ColorChangeSpeed;

	/* Whether to choose initial color randomly or to use InitialColor */
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Lamp")
	bool bRandomInitialColor;

private:
	
	/* Whether the lamp is active */
	UPROPERTY()
	bool bLampActive;

	/* Curernt color of the lamp */
	UPROPERTY()
	FLinearColor CurrentColor;

	/* Lamp dynamic material */
	UPROPERTY()
	class UMaterialInstanceDynamic* LampMID;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 

	/* Called when Character enters the plate referenced by TriggerPlate */
	UFUNCTION(NetMulticast, Reliable)
	void OnTriggerActivated();

	/* Called when Character leaves the plate referenced by TriggerPlate */
	UFUNCTION(NetMulticast, Reliable)
	void OnTriggerDisactivated();

};
