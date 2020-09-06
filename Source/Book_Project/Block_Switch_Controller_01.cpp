// Fill out your copyright notice in the Description page of Project Settings.


#include "Block_Switch_Controller_01.h"
#include "Colored_Floor_Switch.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ABlock_Switch_Controller_01::ABlock_Switch_Controller_01()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
ABlock_Switch_Controller_01::ABlock_Switch_Controller_01(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door To Lerp"));
	//door->AttachTo(RootComponent);

}
ABlock_Switch_Controller_01::~ABlock_Switch_Controller_01()
{
	door = nullptr;
	for (int i = 0; i < switches.Num(); i++)
	{
		switches[i] = nullptr;
		delete switches[i];
	}
	cameraMan = nullptr;

	delete door;
	delete cameraMan;

}
// Called when the game starts or when spawned
void ABlock_Switch_Controller_01::BeginPlay()
{
	Super::BeginPlay();
	numberOfGreenSwitches = 0;
	originalLocation = GetActorLocation();
	for (int i=0;i<switches.Num();i++)
	{
		switches[i]->switchManager = this;
	}

	distance = 0.f;
}

// Called every frame
void ABlock_Switch_Controller_01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock_Switch_Controller_01::incrementSwitchCounter()
{
	numberOfGreenSwitches++;
	if (numberOfGreenSwitches == switches.Num())
	{
		//GetWorldTimerManager().SetTimer(transitionTimer, this, &ABlock_Switch_Controller_01::lerpTheDoor, GetWorld()->GetDeltaSeconds(), true, 0.0f);
		changeCameraPerspective();
	}
}

void ABlock_Switch_Controller_01::decrementSwitchCounter()
{
	if (numberOfGreenSwitches != switches.Num())
	{
		numberOfGreenSwitches--;
	}
}

void ABlock_Switch_Controller_01::beginLerpingProcess()
{
	GetWorldTimerManager().SetTimer(transitionTimer, this, &ABlock_Switch_Controller_01::lerpTheDoor, GetWorld()->GetDeltaSeconds(), true, 0.0f);
	playMovingDoorSound(0);
}

void ABlock_Switch_Controller_01::lerpTheDoor()
{
	distance += GetWorld()->GetDeltaSeconds()/secondsToTransition;
	//distance = FMath::Clamp(distance, 0.f, 1.f);

	FVector newLocation = FMath::Lerp(originalLocation, Destination, distance);
	SetActorLocation(newLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The value of distance is " + FString::SanitizeFloat(distance));
	if (distance >= 1.f || GetActorLocation().Equals(Destination, 0.0f))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::Black, "End of movement");
		playMovingDoorSound(1);
		changeCameraPerspective();
		GetWorldTimerManager().ClearTimer(transitionTimer);
		distance = 0;
	}
}

