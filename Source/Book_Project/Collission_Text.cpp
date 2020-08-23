// Fill out your copyright notice in the Description page of Project Settings.


#include "Collission_Text.h"
#include "Components/BoxComponent.h"
#include "Avatar.h"
#include "Engine/Engine.h"

// Sets default values
ACollission_Text::ACollission_Text()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ACollission_Text::ACollission_Text(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Text Box"));
	triggerBox->AttachTo(RootComponent);
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACollission_Text::Collision);
	//triggerBox->OnComponentEndOverlap.AddDynamic(this, &ACollission_Text::EndCollision);
}
// Called when the game starts or when spawned
void ACollission_Text::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollission_Text::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollission_Text::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{	
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	player = Cast<AAvatar>(OtherActor);
	ShowTutorialText();

	
}

void ACollission_Text::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	HideTutorialText();
}

