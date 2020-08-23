// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Avatar.h"

// Sets default values

ATeleporter::ATeleporter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Boy"));
	collider->AttachTo(RootComponent);
	collider->SetSphereRadius(100);
	collider->SetHiddenInGame(true);
//	collider->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::Teleport);
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::Teleport(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(0,1.f,FColor::Orange,"Our teleporter collider worked");
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		//Cast<AAvatar>(OtherActor)->lerpToDestination(locationtoGoTo);
	}
}

