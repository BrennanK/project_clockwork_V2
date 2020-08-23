// Fill out your copyright notice in the Description page of Project Settings.


#include "Manipulable_Object.h"

// Sets default values
AManipulable_Object::AManipulable_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AManipulable_Object::AManipulable_Object(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManipulable_Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManipulable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AManipulable_Object::interActionCommand()
{
}

void AManipulable_Object::Move()
{
}

