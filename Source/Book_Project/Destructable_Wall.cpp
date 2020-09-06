// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructable_Wall.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestructable_Wall::ADestructable_Wall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ADestructable_Wall::ADestructable_Wall(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	destructionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	destructionBox->AttachTo(RootComponent);
}

ADestructable_Wall::~ADestructable_Wall()
{
	destructionBox = nullptr;
	delete destructionBox;
}

// Called when the game starts or when spawned
void ADestructable_Wall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructable_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructable_Wall::DestroyWall()
{
	Destroy();
}

//void ADestructable_Wall::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//}
//
//void ADestructable_Wall::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//}

