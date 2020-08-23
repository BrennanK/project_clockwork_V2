// Fill out your copyright notice in the Description page of Project Settings.

#include "TArrayExample.h"
#include "Engine/Engine.h"

TArrayExample::TArrayExample()
{
	sample.Add(1);
	sample.Add(10);
	sample.Add(5);
	sample.Add(20);

	for (int index = 0; index < sample.Num(); index++)
	{
		GEngine->AddOnScreenDebugMessage(index, 30.f, FColor::Red, FString::FromInt(sample[index]));
	}
}

TArrayExample::~TArrayExample()
{
}
