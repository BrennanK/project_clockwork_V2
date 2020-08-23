// Fill out your copyright notice in the Description page of Project Settings.

#include "TArrayActor.h"
#include "Engine/Engine.h"
// Sets default values
ATArrayActor::ATArrayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATArrayActor::BeginPlay()
{
	Super::BeginPlay();
	sample.Add(1);
	sample.Add(10);
	sample.Add(5);
	sample.Add(20);

	/*for (int index = 0; index < sample.Num(); index++)
	{
		GEngine->AddOnScreenDebugMessage(index, 3.f, FColor::Red, FString::FromInt(sample[index]));
	}*/

	int count = 0;
	for (TArray<int>::TIterator it = sample.CreateIterator(); it; ++it)
	{
		GEngine->AddOnScreenDebugMessage(count++,8.f,FColor::Red,FString::FromInt(*it));
	}

	//count = 0;

	floaters.Add(1.0f);
	floaters.Add(2.0f);
	floaters.Add(3.0f);
	floaters.Add(1.0f);
	floaters.Add(1.0f);

	for (TSet<float>::TIterator sit = floaters.CreateIterator(); sit; ++sit)
	{
		GEngine->AddOnScreenDebugMessage(count++,9.f,FColor::Green, FString::SanitizeFloat(*sit));
	}

	items.Add("apples", 4);
	items.Add("bowls", 2);
	items.Add("bananas", 10);

	for (TMap<FString, int>::TIterator it = items.CreateIterator(); it; ++it)
	{
		GEngine->AddOnScreenDebugMessage(count++, 10.f, FColor::Blue, it->Key + FString(": ") + FString::FromInt(it->Value));
	}
}

// Called every frame
void ATArrayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

