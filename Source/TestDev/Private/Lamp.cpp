// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	bLampActive = false;
	bRandomInitialColor = false;
	InitialColor = FLinearColor::Red;
	ColorChangeSpeed = 5.0;	

	if (bRandomInitialColor)
		CurrentColor = FLinearColor::MakeRandomColor();
	else
		CurrentColor = InitialColor;
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

	/* Initialize MID for LampMesh */
	LampMID = UMaterialInstanceDynamic::Create(LampMesh->GetMaterial(0), this);
	LampMID->SetScalarParameterValue(TEXT("Emissive Power"), 0.0);
	LampMesh->SetMaterial(0, LampMID);

	
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLampActive)
	{
		/* Convert current color to HSV and shift hue */
		FLinearColor HSV = CurrentColor.LinearRGBToHSV();
		HSV.R += DeltaTime * ColorChangeSpeed;
		CurrentColor = HSV.HSVToLinearRGB();
		
		LampLight->SetLightColor(CurrentColor);
		LampMID->SetVectorParameterValue(TEXT("Color"), CurrentColor);
	}

}

void ALamp::OnTriggerActivated_Implementation()
{
	LampMID->SetScalarParameterValue(TEXT("Emissive Power"), 30.0);
	LampLight->SetIntensity(12000.0);
	bLampActive = true;
}

void ALamp::OnTriggerDisactivated_Implementation()
{
	LampMID->SetScalarParameterValue(TEXT("Emissive Power"), 0.0);
	LampLight->SetIntensity(0.0);
	bLampActive = false;
}

