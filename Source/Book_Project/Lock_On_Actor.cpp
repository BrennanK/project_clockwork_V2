// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock_On_Actor.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
ALock_On_Actor::ALock_On_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
}

ALock_On_Actor::~ALock_On_Actor()
{
	player = nullptr;
	delete player;
}

void ALock_On_Actor::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
}

void ALock_On_Actor::Tick(float DeltaTime)
{
	if (player->isLockedOn == false)
	{
		FVector playerLocation = player->GetActorLocation();
		FVector lockTargetLocation = GetActorLocation();

		FVector distanceBetween = lockTargetLocation - playerLocation;

		float insertIntoRange = FMath::Sqrt(FMath::Square(distanceBetween.X) + FMath::Square(distanceBetween.Y) + FMath::Square(distanceBetween.Z));

		normalizedDistance = UKismetMathLibrary::NormalizeToRange(insertIntoRange, 0, rangeInVectorUnits);

		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "The value of the normalizedDistance is " + FString::SanitizeFloat(normalizedDistance));
		if (normalizedDistance < player->currentClosestWarpOnScaleFromZeroToOne)
		{
			if (normalizedDistance <= closenessRange && normalizedDistance > turnOffRange && player->playerTarget == nullptr)
			{
				LockOn();
				player->playerTarget = this;
			}

			if (normalizedDistance <= turnOffRange) //|| normalizedDistance > 1.0)
			{
				LockOff();
				if (player->playerTarget==this)
				{
					player->playerTarget = nullptr;
				}
				player->currentClosestWarpOnScaleFromZeroToOne = 1.0f;
			}
		}
		else if(normalizedDistance>=1.0 && normalizedDistance<=1.1)
		{
			LockOff();
			player->playerTarget = nullptr;
			player->currentClosestWarpOnScaleFromZeroToOne = 1.0f;
		}
	}
}
