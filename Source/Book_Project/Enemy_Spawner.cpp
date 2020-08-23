// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spawner.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "EnemyCharacter.h"
#include "Patrolling_Enemy.h"
// Sets default values
AEnemy_Spawner::AEnemy_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Spawner::BeginPlay()
{
	Super::BeginPlay();
	initialEnemySpawned = false;
}

// Called every frame
void AEnemy_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy_Spawner::spawnEnemyAfterDelay(float delay)
{
	GetWorld()->GetTimerManager().SetTimer(spawnHandle, this, &AEnemy_Spawner::SpawnEnemy, 1.0f, false, delay);
}

void AEnemy_Spawner::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	//AEnemyCharacter* SpawnedActorRef;

	SpawnedActorRef = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyToSpawn, spawnPoint, GetActorRotation(), SpawnParams);

	SpawnedActorRef->spawnerRef = this;
	SpawnedActorRef->isRespawnable = true;

	if (Cast<APatrolling_Enemy>(SpawnedActorRef))
	{
		Cast<APatrolling_Enemy>(SpawnedActorRef)->spawner=this;
		setPotentialPatrolPath(Cast<APatrolling_Enemy>(SpawnedActorRef));
	}
}

