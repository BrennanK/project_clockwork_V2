// Fill out your copyright notice in the Description page of Project Settings.

#include "Colored_Floor_Switch.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "Block_Switch_Controller_01.h"


AColored_Floor_Switch::AColored_Floor_Switch(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	floorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Floor_Switch_Collider"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
	Mesh->SetupAttachment(RootComponent);
	floorBox->SetupAttachment(Mesh);
	floorBox->OnComponentBeginOverlap.AddDynamic(this, &AColored_Floor_Switch::Collision);

}
// Sets default values


// Called when the game starts or when spawned
void AColored_Floor_Switch::BeginPlay()
{
	Super::BeginPlay();
	isGreen = false;
}

// Called every frame
void AColored_Floor_Switch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColored_Floor_Switch::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (Cast <AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	if (isGreen == false)
	{
		changePanelColorToGreen();
		playSwitchChangeColorSound();
		switchManager->incrementSwitchCounter();
		isGreen = true;
	}
}

