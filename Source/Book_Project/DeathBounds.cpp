// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBounds.h"
#include "Components/BoxComponent.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "Engine/Engine.h"
#include "UI_Data_Holder.h"

// Sets default values
ADeathBounds::ADeathBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ADeathBounds::ADeathBounds(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	deathBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Death Box Collider"));
	deathBox->AttachTo(RootComponent);
	deathBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathBounds::Collision);
}
ADeathBounds::~ADeathBounds()
{
	deathBox = nullptr;
	gameInstance = nullptr;
	player = nullptr;

	delete deathBox;
	delete gameInstance;
	delete player;
}
// Called when the game starts or when spawned
void ADeathBounds::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathBounds::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor)==nullptr)
	{
		return;
	}

	gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	
	if (gameInstance==nullptr)
	{
		return;
	}
	
	gameInstance->incrementDeathNumber();

	playDeathFade();

	player=Cast<AAvatar>(OtherActor);

	/*player->SetActorLocation(gameInstance->Location);

	player->SetActorRotation(gameInstance->Rotation);

	player->GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	if (PController == nullptr)
	{
		return;
	}
	PController->SetControlRotation(gameInstance->Rotation);

	AUI_Data_Holder* UI_Data_Container = Cast<AUI_Data_Holder>(UGameplayStatics::GetActorOfClass(GetWorld(), AUI_Data_Holder::StaticClass()));
	UI_Data_Container->decrementLifeCount();*/
}

void ADeathBounds::resetPlayer()
{
	
	player->SetActorLocation(gameInstance->Location);

	player->SetActorRotation(gameInstance->Rotation);

	player->GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	if (PController == nullptr)
	{
		return;
	}
	PController->SetControlRotation(gameInstance->Rotation);

	AUI_Data_Holder* UI_Data_Container = Cast<AUI_Data_Holder>(UGameplayStatics::GetActorOfClass(GetWorld(), AUI_Data_Holder::StaticClass()));
	UI_Data_Container->decrementLifeCount();
}
