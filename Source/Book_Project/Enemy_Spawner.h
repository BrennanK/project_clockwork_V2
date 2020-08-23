// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.h"
#include "Enemy_Spawner.generated.h"
UCLASS()
class BOOK_PROJECT_API AEnemy_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Spawner();

	UPROPERTY(EditAnywhere, Category = "Enemy to Spawn")
		TSubclassOf<AEnemyCharacter> EnemyToSpawn;

	FTimerHandle spawnHandle;

	UPROPERTY(BlueprintReadWrite)
		FVector spawnPoint;

	UPROPERTY(BlueprintReadWrite)
		bool initialEnemySpawned;

	UPROPERTY(BlueprintReadWrite)
		class AEnemyCharacter* SpawnedActorRef;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void spawnEnemyAfterDelay(float delay);
	
	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent)
		void setPotentialPatrolPath(APatrolling_Enemy* spawn);
};
