// Fill out your copyright notice in the Description page of Project Settings.

#include "Starting_Point.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Sets default values
AStarting_Point::AStarting_Point()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AStarting_Point::~AStarting_Point()
{
	PController = nullptr;

	delete PController;
}

// Called when the game starts or when spawned
void AStarting_Point::BeginPlay()
{
	Super::BeginPlay();

	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	avatar->SetActorLocation(GetActorLocation());
	avatar->SetActorRotation(GetActorRotation());
	
	PController=GetWorld()->GetFirstPlayerController();
	if (PController == nullptr)
	{
		return;
	}
	PController->SetControlRotation(GetActorRotation());
	avatar->LookUpAtRate(initialLookRate);
}

// Called every frame
void AStarting_Point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

