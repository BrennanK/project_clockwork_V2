// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBounce_Pad.h"
#include "Engine/Engine.h"
#include "Avatar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
ANewBounce_Pad::ANewBounce_Pad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ANewBounce_Pad::ANewBounce_Pad(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bounceBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	Mesh->AttachTo(RootComponent);
	bounceBox->AttachTo(Mesh);
	bounceBox->OnComponentBeginOverlap.AddDynamic(this, &ANewBounce_Pad::Collision);
	bounceBox->OnComponentEndOverlap.AddDynamic(this, &ANewBounce_Pad::EndCollision);
}
ANewBounce_Pad::~ANewBounce_Pad()
{
	bounceBox = nullptr;
	Mesh = nullptr;

	delete bounceBox;
	delete Mesh;
}
void ANewBounce_Pad::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetActorLocation();
}

void ANewBounce_Pad::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast <AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	AAvatar* player = Cast<AAvatar>(OtherActor);
	player->changeToBouncePadAirControl();
	switch (typeOfPad)
	{
	case EBOUNCE::Single:
		player->LaunchCharacter(FVector(0, 0, maxBounceHeight), true, true);
		break;

	case EBOUNCE::Build_Up:
		if (player->timeFalling*bounceHeightPerSecondFalling < minBounceHeight)
		{
			player->LaunchCharacter(FVector(0, 0, minBounceHeight), true, true);
			player->isFalling = false;
			player->timeFalling = 0.0f;
		}
		else if (player->timeFalling*bounceHeightPerSecondFalling > maxBounceHeight)
		{
			player->LaunchCharacter(FVector(0, 0, maxBounceHeight), true, true);
			player->isFalling = false;
			player->timeFalling = 0.0f;
		}
		else
		{
			player->LaunchCharacter(FVector(0, 0, player->timeFalling*bounceHeightPerSecondFalling), true, true);
			player->isFalling = false;
			player->timeFalling = 0.0f;
		}
		break;
	default:
		break;
	}
}

void ANewBounce_Pad::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast <AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	AAvatar* player = Cast<AAvatar>(OtherActor);
	player->isFalling = true;
}

void ANewBounce_Pad::interActionCommand()
{
	GetWorldTimerManager().SetTimer(movementTimer, this, &ANewBounce_Pad::Move, GetWorld()->GetDeltaSeconds(), true, 0.0f);
}

void ANewBounce_Pad::Move()
{
	lerpAlpha += GetWorld()->GetDeltaSeconds();
	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);

	FVector newLocation = FMath::Lerp(originalLocation, destination, lerpAlpha);
	SetActorLocation(newLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The value of lerpAlpha is " + FString::SanitizeFloat(lerpAlpha));
	if (lerpAlpha >= 1.f)
	{
		bounceBox->SetGenerateOverlapEvents(true);
		//changeCameraPerspective();
		GetWorldTimerManager().ClearTimer(movementTimer);
		lerpAlpha = 0;
	}
}
