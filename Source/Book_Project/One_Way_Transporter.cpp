// Fill out your copyright notice in the Description page of Project Settings.


#include "One_Way_Transporter.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AOne_Way_Transporter::AOne_Way_Transporter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionBox= CreateDefaultSubobject<UBoxComponent>(TEXT(" Transporter Collider"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AOne_Way_Transporter::Collision);
	collisionBox->OnComponentEndOverlap.AddDynamic(this, &AOne_Way_Transporter::EndCollision);
}

void AOne_Way_Transporter::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor)==nullptr)
	{
		return;
	}
	GetWorldTimerManager().ClearTimer(transitionTimer);
	destinationOfMovement = pathStartOrEnd;
	locationBeforeTransitionStart = GetActorLocation();
	GetWorldTimerManager().SetTimer(transitionTimer, this, &AOne_Way_Transporter::moveToDestination, GetWorld()->GetDeltaSeconds(), true, 1.5f);
}

void AOne_Way_Transporter::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	GetWorldTimerManager().ClearTimer(transitionTimer);
	destinationOfMovement = originalLocation;
	locationBeforeTransitionStart = GetActorLocation();
	GetWorldTimerManager().SetTimer(transitionTimer, this, &AOne_Way_Transporter::moveToDestination, .01, true, 1.5f);
}

// Called when the game starts or when spawned
void AOne_Way_Transporter::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetActorLocation();
}

// Called every frame
void AOne_Way_Transporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOne_Way_Transporter::moveToDestination()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds() / timeToTransition;
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);
	FVector newLocation = FMath::Lerp(locationBeforeTransitionStart, destinationOfMovement, lerpAlpha);
	SetActorLocation(newLocation);

	if (lerpAlpha >= 1.f)
	{
		//activatePlayerActionSound(6);
		GetWorldTimerManager().ClearTimer(transitionTimer);		
		lerpAlpha = 0.0f;
	}
}

