// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"
UENUM() enum class ETurretType: uint8{Standard,Tracking};
UCLASS()
class BOOK_PROJECT_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();
	
	UPROPERTY(EditAnywhere,Category="Actor to Spawn")
	TArray<TSubclassOf<AActor>> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Properties of Spawn")
		ETurretType typeOfTurret;
	
	UPROPERTY(EditAnywhere, Category = "Properties of Spawn")
		float  delayOfFire;

	UPROPERTY(EditAnywhere, Category = "Properties of Spawn")
		float ProjectileSpeed;

	UPROPERTY(EditAnywhere, Category = "Properties of Spawn")
		float ProjectileLifeTime;

	FTimerHandle fireTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void SpawnObject();
	FVector Loc;
	FRotator Rot;

	UFUNCTION()
		void stopFiring();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
