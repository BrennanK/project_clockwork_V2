// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Avatar.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "Engine/Engine.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ACheckpoint::ACheckpoint(const FObjectInitializer &ObjectInitializer): Super(ObjectInitializer)
{
	checkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Check Box"));
	checkBox->AttachTo(RootComponent);
	checkBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::Collision);
}
// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Checkpoint achieved");
	if (Cast<AAvatar>(OtherActor)==nullptr)
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Checkpoint achieved past IF STAEMENT");
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	
	gameInstance->Location = GetActorLocation();
	gameInstance->Rotation = GetActorRotation();

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "The value for location of checkpint is"+ FString::SanitizeFloat(gameInstance->Location.X));
}

