// Fill out your copyright notice in the Description page of Project Settings.


#include "Retractable_Platform.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "TimerManager.h"

ARetractable_Platform::ARetractable_Platform(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	movingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Movable Mesh"));
	movingMesh->AttachTo(RootComponent);
	
}

void ARetractable_Platform::BeginPlay()
{
	Super::BeginPlay();
	shouldChange = false;
	if (autoActivate==true)
	{
		interActionCommand();
	}
}

void ARetractable_Platform::interActionCommand()
{
	doWeChangeDirections();
	switch ((int)direction)
	{
	case 1:
		activatePlatformMovementSound(0);
		break;

	case -1:
		activatePlatformMovementSound(1);
		break;
	}
	GetWorldTimerManager().SetTimer(movementTimer,this,&ARetractable_Platform::Move,.01f,true,initialDelay);
}

void ARetractable_Platform::doWeChangeDirections()
{
	if (shouldChange)
	{
		direction *= -1;
		shouldChange = false;
	}
}

void ARetractable_Platform::Move()
{
	FVector movePlatformToThisLocation;
	FVector originalLocation;
	if (direction == 1)
	{
		movePlatformToThisLocation = LocationWhenExtended;
		originalLocation = locationWhenRetracted;
		//activatePlatformMovementSound(0);
	}
	else
	{
		movePlatformToThisLocation = locationWhenRetracted;
		originalLocation = LocationWhenExtended;
		//activatePlatformMovementSound(1);
	}

	lerpAlpha += GetWorld()->GetDeltaSeconds();
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FVector newLocation = FMath::Lerp(originalLocation, movePlatformToThisLocation, lerpAlpha);

	movingMesh->SetRelativeLocation(newLocation);

	if (lerpAlpha >= 1.0f)
	{
		lerpAlpha = 0;
		shouldChange = true;
		GetWorldTimerManager().SetTimer(resetCycle, this, &ARetractable_Platform::interActionCommand, 1.0f, false, movementDelay);
		GetWorldTimerManager().ClearTimer(movementTimer);
		initialDelay = 0;
	}
}
