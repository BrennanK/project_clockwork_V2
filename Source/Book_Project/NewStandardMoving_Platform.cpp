// Fill out your copyright notice in the Description page of Project Settings.


#include "NewStandardMoving_Platform.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ANewStandardMoving_Platform::ANewStandardMoving_Platform()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ANewStandardMoving_Platform::BeginPlay()
{
	Super::BeginPlay();
	originalX = GetActorLocation().X;
	originalY = GetActorLocation().Y;
	originalZ = GetActorLocation().Z;
}

void ANewStandardMoving_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	switch (direction)
	{
	case EDIRECTIONOFMOVEMENT::X:

		if (Location.X >= originalX + rangeOfMovement)
		{
			amountToMove *= -1;
		}
		else if (Location.X <= originalX - rangeOfMovement)
		{
			amountToMove *= -1;
		}

		SetActorLocation(FVector(Location.X + amountToMove, Location.Y, Location.Z));


		break;

	case EDIRECTIONOFMOVEMENT::Y:

		if (Location.Y >= originalY + rangeOfMovement)
		{
			amountToMove *= -1;
			SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));
		}
		else if (Location.Y <= originalY - rangeOfMovement)
		{
			amountToMove *= -1;
			//
			//SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));  

		}

		SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));


		break;
	case EDIRECTIONOFMOVEMENT::Z:

		if (Location.Z >= originalZ + rangeOfMovement)
		{
			amountToMove *= -1;
		}
		else if (Location.Z <= originalZ - rangeOfMovement)
		{
			amountToMove *= -1;
		}

		SetActorLocation(FVector(Location.X, Location.Y, Location.Z + amountToMove));

		break;
	default:
		break;
	}
}

void ANewStandardMoving_Platform::interActionCommand()
{
	GetWorldTimerManager().SetTimer(movementTimer, this, &ANewStandardMoving_Platform::Move, GetWorld()->GetDeltaSeconds(), true, 0.0f);
}

void ANewStandardMoving_Platform::Move()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds();
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FVector newLocation = FMath::Lerp(originalLocation, destination, lerpAlpha);
	SetActorLocation(newLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The value of lerpAlpha is " + FString::SanitizeFloat(lerpAlpha));
	if (lerpAlpha >= 1.f)
	{
		//changeCameraPerspective();
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0;
	}
}
