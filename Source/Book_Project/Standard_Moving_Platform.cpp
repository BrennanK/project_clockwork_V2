// Fill out your copyright notice in the Description page of Project Settings.

#include "Standard_Moving_Platform.h"
#include "Engine/Engine.h"

// Sets default values
AStandard_Moving_Platform::AStandard_Moving_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStandard_Moving_Platform::BeginPlay()
{
	Super::BeginPlay();
	originalX = GetActorLocation().X;
	originalY = GetActorLocation().Y;
	originalZ = GetActorLocation().Z;
}

// Called every frame
void AStandard_Moving_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector Location = GetActorLocation();
	//switch (direction)
	//{
	//case EDIRECTIONOFMOVEMENT::X :
	//	
	//	if (Location.X >= originalX + rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//	}
	//	else if (Location.X <= originalX - rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//	}
	//	
	//		SetActorLocation(FVector(Location.X + amountToMove, Location.Y, Location.Z));
	//	

	//	break;

	//case EDIRECTIONOFMOVEMENT::Y:
	//	
	//	if (Location.Y >= originalY + rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//		SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));
	//	}
	//	else if (Location.Y <= originalY - rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//		//
	//		//SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));  
	//		
	//	}
	//	
	//		SetActorLocation(FVector(Location.X, Location.Y + amountToMove, Location.Z));
	//	

	//	break;
	//case EDIRECTIONOFMOVEMENT::Z:
	//	
	//	if (Location.Z >= originalZ + rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//	}
	//	else if (Location.Z <= originalZ - rangeOfMovement)
	//	{
	//		amountToMove *= -1;
	//	}
	//	
	//		SetActorLocation(FVector(Location.X, Location.Y, Location.Z + amountToMove));

	//	break;
	//default:
	//	break;
	//}
}
