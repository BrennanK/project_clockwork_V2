// Fill out your copyright notice in the Description page of Project Settings.

#include "Working_Bouncepad.h"
#include "Engine/Engine.h"
#include "Avatar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
AWorking_Bouncepad::AWorking_Bouncepad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AWorking_Bouncepad::AWorking_Bouncepad(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bounceBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	Mesh->AttachTo(RootComponent);
	bounceBox->AttachTo(Mesh);
	//bounceBox->OnComponentBeginOverlap.AddDynamic(this, &AWorking_Bouncepad::Collision);
	//bounceBox->OnComponentEndOverlap.AddDynamic(this, &AWorking_Bouncepad::EndCollision);
}

// Called when the game starts or when spawned
void AWorking_Bouncepad::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetActorLocation();
}

// Called every frame
void AWorking_Bouncepad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AWorking_Bouncepad::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//
//	if (Cast <AAvatar>(OtherActor) == nullptr)
//	{
//		return;
//	}
//	AAvatar* player = Cast<AAvatar>(OtherActor);
//	switch (padType)
//	{
//		case EBOUNCE_TYPE::Single:
//			player->LaunchCharacter(FVector(0, 0, maxBounceHeight), true, true);
//			break;
//
//		case EBOUNCE_TYPE::Build_Up:
//			if (player->timeFalling*bounceHeightPerSecondFalling < minBounceHeight)
//			{
//				player->LaunchCharacter(FVector(0, 0, minBounceHeight), true, true);
//				player->isFalling = false;
//				player->timeFalling = 0.0f;
//			}
//			else if (player->timeFalling*bounceHeightPerSecondFalling > maxBounceHeight)
//			{
//				player->LaunchCharacter(FVector(0, 0, maxBounceHeight), true, true);
//				player->isFalling = false;
//				player->timeFalling = 0.0f;
//			}
//			else
//			{
//				player->LaunchCharacter(FVector(0, 0, player->timeFalling*bounceHeightPerSecondFalling), true, true);
//				player->isFalling = false;
//				player->timeFalling = 0.0f;
//			}
//			break;
//		default:
//			break;
//	}
//
//	
//	
//}
//
//void AWorking_Bouncepad::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	if (Cast <AAvatar>(OtherActor) == nullptr)
//	{
//		return;
//	}
//	AAvatar* player = Cast<AAvatar>(OtherActor);
//	player->isFalling = true;
//}
//
//void AWorking_Bouncepad::interActionCommand()
//{
//	GetWorldTimerManager().SetTimer(movementTimer, this, &AWorking_Bouncepad::Move, GetWorld()->GetDeltaSeconds(), true, 0.0f);
//}
//
//
//void AWorking_Bouncepad::Move()
//{
//	lerpAlpha += GetWorld()->GetDeltaSeconds();
//	lerpAlpha = FMath::Clamp(lerpAlpha, 0.f, 1.f);
//
//	FVector newLocation = FMath::Lerp(originalLocation, destination, lerpAlpha);
//	SetActorLocation(newLocation);
//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The value of lerpAlpha is " + FString::SanitizeFloat(lerpAlpha));
//	if (lerpAlpha >= 1.f )
//	{
//		bounceBox->SetGenerateOverlapEvents(true);
//		//changeCameraPerspective();
//		GetWorldTimerManager().ClearTimer(movementTimer);
//		lerpAlpha = 0;
//	}
//}

