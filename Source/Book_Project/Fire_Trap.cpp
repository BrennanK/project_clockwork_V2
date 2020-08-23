// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire_Trap.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Particles/ParticleSystemComponent.h"
#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
AFire_Trap::AFire_Trap()
{

}

AFire_Trap::AFire_Trap(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	fireBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	
	fireParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particle"));
	
	waterParticle= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Water Particle"));

	//fireParticle->AttachTo(RootComponent);
	RootComponent = fireParticle;
	fireBox->AttachTo(fireParticle);
	waterParticle->AttachTo(fireBox);

	fireBox->OnComponentBeginOverlap.AddDynamic(this, &AFire_Trap::Collision);
}

void AFire_Trap::BeginPlay()
{
	Super::BeginPlay();
	if (activateOnPlay == false)
	{
		fireParticle->DeactivateSystem();
		fireBox->SetGenerateOverlapEvents(false);
	}
	else
	{
		turnOnFireSound();
	}
}

void AFire_Trap::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor))
	{
		AAvatar* player = Cast<AAvatar>(OtherActor);

		FRotator lookAtPlayer= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());

		player->addKnockback(lookAtPlayer);

		player->MinusHealth(damageToPlayer);
	}
}

void AFire_Trap::interActionCommand()
{
	playWaterSoundEffect(0);
	GetWorldTimerManager().SetTimer(movementTimer, this, &AFire_Trap::douseFire, 1.0f, false, delayToTurnWaterOn);
	float douseWaterDelay = delayToTurnFireOff + delayToTurnWaterOn;
	GetWorldTimerManager().SetTimer(fireOffHandle, this, &AFire_Trap::deactivateFire, 1.0f, false, delayToTurnFireOff);
	float totalDelayForEffects = delayToTurnWaterOn+ delayToTurnFireOff + delayToTurnWaterOff;
	GetWorldTimerManager().SetTimer(turnOffHandle, this, &AFire_Trap::turnOffWater, 1.0f, false, totalDelayForEffects);
}

void AFire_Trap::douseFire()
{
	waterParticle->ActivateSystem();
	playWaterSoundEffect(1);
}

void AFire_Trap::deactivateFire()
{
	fireParticle->DeactivateSystem();
	turnOffFireSound();
	fireBox->SetGenerateOverlapEvents(false);
}

void AFire_Trap::turnOffWater()
{
	waterParticle->DeactivateSystem();
	playWaterSoundEffect(2);
}


