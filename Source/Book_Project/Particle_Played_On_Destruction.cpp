// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle_Played_On_Destruction.h"
#include "TimerManager.h"

// Sets default values
AParticle_Played_On_Destruction::AParticle_Played_On_Destruction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticle_Played_On_Destruction::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(particleTimer, this, &AParticle_Played_On_Destruction::DestroyParticle, 1.0f, false, lifeTime);
}

// Called every frame
void AParticle_Played_On_Destruction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticle_Played_On_Destruction::DestroyParticle()
{
	Destroy();
}

