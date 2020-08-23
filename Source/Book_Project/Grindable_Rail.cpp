// Fill out your copyright notice in the Description page of Project Settings.


#include "Grindable_Rail.h"

// Sets default values
AGrindable_Rail::AGrindable_Rail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrindable_Rail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrindable_Rail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

