// Fill out your copyright notice in the Description page of Project Settings.


#include "Math_Answer_Display.h"
#include "Engine/Engine.h"
// Sets default values
AMath_Answer_Display::AMath_Answer_Display()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMath_Answer_Display::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "This is section 2. ");
	slopeChallenge();
}

// Called every frame
void AMath_Answer_Display::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AMath_Answer_Display::pointOnLine(const int & m, const int & b, const int & t)
{
	int c = m - (b*t);
	return c;
}

int AMath_Answer_Display::slopeGradientCalc(int & x1, int & x2, int & y1, int & y2)
{
	return (y2-y1)/(x2-x1);
}

void AMath_Answer_Display::slopeChallenge()
{
	int c1 = pointOnLine(m, b, 0);
	int c2 = pointOnLine(m, b, 10);
	int c3 = pointOnLine(m, b, 30);
	int c4 = pointOnLine(m, b, 50);

	int x1 = 30;
	int x2 = 50;

	int slope = slopeGradientCalc(x1, x2, c3, c4);

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, "The coordinate pair are (" + FString::FromInt(0) + "," + FString::FromInt(c1));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, "The coordinate pair are (" + FString::FromInt(10) + "," + FString::FromInt(c2));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, "The coordinate pair are (" + FString::FromInt(30) + "," + FString::FromInt(c3));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, "The coordinate pair are (" + FString::FromInt(50) + "," + FString::FromInt(c4));

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, "The slope is " + FString::FromInt(slope));
}

