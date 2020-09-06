// Fill out your copyright notice in the Description page of Project Settings.


#include "Energy_Restorer.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Avatar.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

AEnergy_Restorer::AEnergy_Restorer()
{
	PrimaryActorTick.bCanEverTick = true;
}

AEnergy_Restorer::AEnergy_Restorer(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	restorationParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Restoration Particle"));
	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Restoration Sphere"));
	restorationParticle->AttachTo(RootComponent);
	sphereCollider->AttachTo(restorationParticle);
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnergy_Restorer::Collision);
	sphereCollider->OnComponentEndOverlap.AddDynamic(this, &AEnergy_Restorer::EndCollision);
}

AEnergy_Restorer::~AEnergy_Restorer()
{
	restorationParticle = nullptr;
	sphereCollider = nullptr;
	player = nullptr;

	delete player;
	delete sphereCollider;
	delete restorationParticle;
}

void AEnergy_Restorer::BeginPlay()
{
	Super::BeginPlay();
}

void AEnergy_Restorer::interActionCommand()
{
}

void AEnergy_Restorer::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Emerald, "We are colliding with the restorer");
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}

	player = Cast<AAvatar>(OtherActor);
	if (player->continuousPowerOn == true)
	{
		player->shutOffContinuousTimePower();
	}
	originalAmountOfEnergy = player->currentEnergy;
	player->changeToEnergyMaterial();
	GetWorld()->GetTimerManager().SetTimer(movementTimer, this, &AEnergy_Restorer::Move, GetWorld()->GetDeltaSeconds(), true, 0.f);
}

void AEnergy_Restorer::Move()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds();
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	player->currentEnergy = FMath::Lerp(originalAmountOfEnergy, player->maxEnergy, lerpAlpha);
	player->callEnergyBarChange();

	if (lerpAlpha >= 1.f)
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0;
		player->changeToNormalMaterial();
	}

}

void AEnergy_Restorer::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AAvatar>(OtherActor))
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0;
		player->changeToNormalMaterial();
	}
}
