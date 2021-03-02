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

	RootComponent = PlateCollision;
	PlateMesh->SetupAttachment(PlateCollision);

	SetReplicates(true);

	bStepped = false;
	bPlateMoving = false;
	NormalPlateLocation = PlateMesh->GetRelativeLocation();
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

	if (bPlateMoving)
	{
		if (bStepped)
		{
			/* Update plate position when player stepped on it */
			FVector Target = NormalPlateLocation - FVector(0.0, 0.0, 12.0);
			FVector NewPosition = FMath::VInterpTo(PlateMesh->GetRelativeLocation(), Target, DeltaTime, 20.0);
			PlateMesh->SetRelativeLocation(NewPosition);

			/* Disable movement when target achieved */
			if (FVector::PointsAreNear(Target, NewPosition, 0.1)) bPlateMoving = false;
		}
		else
		{
			/* Update plate position when player left it */
			FVector Target = NormalPlateLocation;
			FVector NewPosition = FMath::VInterpTo(PlateMesh->GetRelativeLocation(), Target, DeltaTime, 20.0);
			PlateMesh->SetRelativeLocation(NewPosition);

			/* Disable movement when target achieved */
			if (FVector::PointsAreNear(Target, NewPosition, 0.1)) bPlateMoving = false;
		}
	}
}


void APressurePlate::OnTriggerEntered(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATestDevCharacter* Character = Cast<ATestDevCharacter>(OtherActor);

	if (HasAuthority() && Character)
	{
		OnPlateEntered.Broadcast();
		bStepped = true;
		bPlateMoving = true;
	}
}


void APressurePlate::OnTriggerLeaved(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATestDevCharacter* Character = Cast<ATestDevCharacter>(OtherActor);

	if (HasAuthority() && Character)
	{
		OnPlateLeaved.Broadcast();
		bStepped = false;
		bPlateMoving = true;
	}
}
