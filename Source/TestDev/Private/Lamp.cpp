// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "PressurePlate.h"

// Sets default values
ALamp::ALamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lamp Mesh"));
	LampLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Lamp Light"));

	RootComponent = LampMesh;
	LampLight->SetupAttachment(LampMesh);

	SetReplicates(true);
	LampLight->SetIntensity(0.0);

}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerPlate)
	{
		TriggerPlate->OnPlateEntered.AddUFunction(this, TEXT("OnTriggerActivated"));
		TriggerPlate->OnPlateLeaved.AddUFunction(this, TEXT("OnTriggerDisactivated"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger wasn't specified for lamp %s"), *GetName());
	}
	
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALamp::OnTriggerActivated_Implementation()
{
	LampLight->SetIntensity(6000.0);
}

void ALamp::OnTriggerDisactivated_Implementation()
{
	LampLight->SetIntensity(0.0);
}

