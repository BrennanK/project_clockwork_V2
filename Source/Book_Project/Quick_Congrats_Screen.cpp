// Fill out your copyright notice in the Description page of Project Settings.


#include "Quick_Congrats_Screen.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Avatar.h"

// Sets default values
AQuick_Congrats_Screen::AQuick_Congrats_Screen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AQuick_Congrats_Screen::AQuick_Congrats_Screen(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX FOR CONGRATS"));
	boxCollider->AttachTo(RootComponent);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AQuick_Congrats_Screen::Collision);
}

AQuick_Congrats_Screen::~AQuick_Congrats_Screen()
{
	boxCollider = nullptr;
	delete boxCollider;
}

// Called when the game starts or when spawned
void AQuick_Congrats_Screen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuick_Congrats_Screen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuick_Congrats_Screen::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Cast<AAvatar>(OtherActor)->currentState = ECharacterState::DEAD;
	showCongrats();
}

