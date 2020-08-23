// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrolling_Enemy.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Avatar.h"
#include "Engine.h"
#include "EnemyCharacter.h"
#include "Enemy_Spawner.h"
#include "Particle_Played_On_Destruction.h"
#include "Destructable_Wall.h"

APatrolling_Enemy::APatrolling_Enemy(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	explosionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Radius"));
	explosionRadius->AttachTo(RootComponent);
	explosionRadius->OnComponentBeginOverlap.AddDynamic(this, &APatrolling_Enemy::Collision);
	explosionRadius->OnComponentEndOverlap.AddDynamic(this, &APatrolling_Enemy::EndCollision);
}

void APatrolling_Enemy::DestroyThisUnit()
{
	playFuseLightSound();
	playPunchImpactSound();
	GetWorldTimerManager().SetTimer(blinkHandle, this, &APatrolling_Enemy::initiateSpeedChange, 1.0f, false, slowBlinkDelay);
	float timeOfExplosion = slowBlinkDelay + secondsBetweenFastBlinkAndBlowUp;
	GetWorldTimerManager().SetTimer(deathHandle, this, &APatrolling_Enemy::DestroyCaller, 1.0f, false, timeOfExplosion);
}

void APatrolling_Enemy::Die()
{
	if (isRespawnable == true)
	{
		delayOfRespawn = 1.0f;
		spawnerRef->spawnEnemyAfterDelay(delayOfRespawn);
		//Destroy();
	}
	Destroy();
}

void APatrolling_Enemy::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "Our explosion sphere for the patrol character is functioning bitches");
	if (Cast<AAvatar>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "Our explosion sphere for the patrol character is functioning bitches");
		playerCharacter = Cast<AAvatar>(OtherActor);
	}

	if (Cast<ADestructable_Wall>(OtherActor))
	{
		wall = Cast<ADestructable_Wall>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "The wall has been found");
	}
}

void APatrolling_Enemy::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AAvatar>(OtherActor))
	{
		playerCharacter = nullptr;
	}
	
	if (Cast<ADestructable_Wall>(OtherActor))
	{
		wall = nullptr;
	}
}

void APatrolling_Enemy::BeginPlay()
{
	Super::BeginPlay();
	explosionRadius->OnComponentBeginOverlap.AddDynamic(this, &APatrolling_Enemy::Collision);
	explosionRadius->OnComponentEndOverlap.AddDynamic(this, &APatrolling_Enemy::EndCollision);
	//GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "Our begin play for the patrol character is functioning");
}

void APatrolling_Enemy::initiateSpeedChange()
{
	changeSpeedOfBlink();
}

void APatrolling_Enemy::DestroyCaller()
{
	stopFuseLightSound();
	//playerCharacter->activateSoundFromDestroyedActor(8);
	/*TArray<FHitResult> OutHit;

	FVector MyLocation = GetActorLocation();

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.f);

	DrawDebugSphere(GetWorld(), MyLocation, MyColSphere.GetSphereRadius(),50, FColor::Cyan,true);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHit, MyLocation, MyLocation, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "Our hit sphere for the patrol character is functioning");
	}*/
	if (playerCharacter)
	{
		//playerCharacter->skeleton->AddRadialImpulse(GetActorLocation(), 250.f, 5000.f, ERadialImpulseFalloff::RIF_Constant, true);
		FRotator lookAtPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerCharacter->GetActorLocation());
		playerCharacter->addKnockback(lookAtPlayer);
		playerCharacter->MinusHealth(damageToDeal);
		playerCharacter->activateSoundFromDestroyedActor(8);
	}

	if (wall)
	{
		wall->DestroyWall();
	}

	FActorSpawnParameters SpawnParams;
	AParticle_Played_On_Destruction* SpawnedActorRef;

	SpawnedActorRef = GetWorld()->SpawnActor<AParticle_Played_On_Destruction>(particleToSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);
	Die();
	//Destroy();
}