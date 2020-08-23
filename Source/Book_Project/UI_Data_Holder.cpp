// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Data_Holder.h"

// Sets default values
AUI_Data_Holder::AUI_Data_Holder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUI_Data_Holder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUI_Data_Holder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUI_Data_Holder::incrementD_FragCount(int valueOfFragment)
{
	D_Frag_Count += valueOfFragment;
	updateFragmentCount(D_Frag_Count);
}

void AUI_Data_Holder::incrementTA_FragCount()
{
	TA_Frag_Count++;
	updateAbilityShardCount();
}

void AUI_Data_Holder::incrementLifeCount()
{
	Life_Obtained_Count++;
	updateLifeCount();
}

void AUI_Data_Holder::decrementLifeCount()
{
	Life_Obtained_Count--;
	updateLifeCount();
}

