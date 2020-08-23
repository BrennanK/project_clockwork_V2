// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Projectile.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Loc = GetActorLocation();
	Rot = GetActorRotation();
	GetWorldTimerManager().SetTimer(fireTimer, this, &ATurret::SpawnObject, delayOfFire, true, delayOfFire);
}

void ATurret::SpawnObject()
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef;
	switch (typeOfTurret)
	{
		case ETurretType::Standard:
			SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn[0], Loc, Rot, SpawnParams);
			if (Cast<AProjectile>(SpawnedActorRef))
			{
				Cast<AProjectile>(SpawnedActorRef)->speed = ProjectileSpeed;
				Cast<AProjectile>(SpawnedActorRef)->lifeTime = ProjectileLifeTime;
			}
			break;
		case ETurretType::Tracking:
			SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn[1], Loc, Rot, SpawnParams);
			if (Cast<AProjectile>(SpawnedActorRef))
			{
				Cast<AProjectile>(SpawnedActorRef)->speed = ProjectileSpeed;
				Cast<AProjectile>(SpawnedActorRef)->lifeTime = ProjectileLifeTime;
			}
			break;
		default:
			break;
	}
}

void ATurret::stopFiring()
{
	GetWorldTimerManager().ClearTimer(fireTimer);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

