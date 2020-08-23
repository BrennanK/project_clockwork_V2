// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Avatar.h"
#include "TimerManager.h"
#include "Engine.h"
ATrap_Door::ATrap_Door()
{

}

ATrap_Door::ATrap_Door(const FObjectInitializer &ObjectInitializer)
{
	rotatingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating Cylinder"));
	activationBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger box"));
	activationBox->OnComponentBeginOverlap.AddDynamic(this,&ATrap_Door::Collision);
}

void ATrap_Door::BeginPlay()
{
	Super::BeginPlay();
}

void ATrap_Door::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "The trap door notices collision");
	if (Cast<AAvatar>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "The trap door notices that we are the player");
		interActionCommand();
	}
}

void ATrap_Door::interActionCommand()
{
	activationBox->SetGenerateOverlapEvents(false);
	playCorrectSound(0);
	GetWorldTimerManager().SetTimer(movementTimer, this, &ATrap_Door::beforeDropVisualDown, .01f, true, 0.0f);
}

void ATrap_Door::beforeDropVisualDown()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds() / (rateOfWarning / 2);
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FRotator newRotation = FMath::Lerp(rotationAtZeroInfluence, endRotationOfVisualWarning, lerpAlpha);

	SetActorRotation(newRotation);

	if (lerpAlpha>=1.0f)
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0.f;
		GetWorldTimerManager().SetTimer(movementTimer, this, &ATrap_Door::beforeDropVisualUp, .01f, true, 0.0f);
	}
}

void ATrap_Door::beforeDropVisualUp()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds() / (rateOfWarning / 2);
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FRotator newRotation = FMath::Lerp(endRotationOfVisualWarning, rotationAtZeroInfluence, lerpAlpha);

	SetActorRotation(newRotation);

	if (lerpAlpha >= 1.0f)
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0.f;
		playCorrectSound(1);
		GetWorldTimerManager().SetTimer(movementTimer, this, &ATrap_Door::platformDrop, .01f, true, 0.0f);
	}
}

void ATrap_Door::platformDrop()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds() / rateOfFalling;
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FRotator newRotation = FMath::Lerp(rotationAtZeroInfluence, endRotationOfVisualDrop, lerpAlpha);

	SetActorRotation(newRotation);

	if (lerpAlpha >= 1.0f)
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0.f;
		GetWorldTimerManager().SetTimer(movementTimer, this, &ATrap_Door::platformReset, .01f, true, 3.0f);
	}
}

void ATrap_Door::platformReset()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds() / rateOfReset;
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FRotator newRotation = FMath::Lerp(endRotationOfVisualDrop, rotationAtZeroInfluence, lerpAlpha);

	SetActorRotation(newRotation);

	if (lerpAlpha >= 1.0f)
	{
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0.f;
		activationBox->SetGenerateOverlapEvents(true);
	}
}

