// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TestDev/TestDevCharacter.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate Mesh"));
	PlateCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Plate Collision"));

	RootComponent = PlateMesh;
	PlateCollision->SetupAttachment(PlateMesh);

	SetReplicates(true);
	
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	PlateCollision->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnTriggerEntered);
	PlateCollision->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnTriggerLeaved);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APressurePlate::OnTriggerEntered(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATestDevCharacter* Character = Cast<ATestDevCharacter>(OtherActor);

	if (HasAuthority())
	{
		OnPlateEntered.Broadcast();
	}
}


void APressurePlate::OnTriggerLeaved(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		OnPlateLeaved.Broadcast();
	}
}
