// Fill out your copyright notice in the Description page of Project Settings.

#include "Distortion_Fragments.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "UI_Data_Holder.h"
// Sets default values
ADistortion_Fragments::ADistortion_Fragments()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ADistortion_Fragments::ADistortion_Fragments(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Sphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Model"));
	Mesh->AttachTo(RootComponent);
	sphereCollider->AttachTo(Mesh);
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ADistortion_Fragments::Collision);
}

ADistortion_Fragments::~ADistortion_Fragments()
{
	sphereCollider = nullptr;
	Mesh = nullptr;
	UI_Data_Container = nullptr;

	delete sphereCollider;
	delete Mesh;
	delete UI_Data_Container;
}

// Called when the game starts or when spawned
void ADistortion_Fragments::BeginPlay()
{
	Super::BeginPlay();

	UI_Data_Container=Cast<AUI_Data_Holder>(UGameplayStatics::GetActorOfClass(GetWorld(), AUI_Data_Holder::StaticClass()));

	decideWhatToIncrementInUIDataHolder();
}

void ADistortion_Fragments::decideWhatToIncrementInUIDataHolder()
{
	switch (typeOfPickUp)
	{
	case EPickupType::DistortionFragments:
		UI_Data_Container->D_Frag_MaxValue+=fragmentValue;
		break;

	case EPickupType::TimeAbilityShards:
		UI_Data_Container->TA_Frag_MaxValue++;
		break;
	
	case EPickupType::Lives:
		UI_Data_Container->Lives_MaxValue++;
	}
}

// Called every frame
void ADistortion_Fragments::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADistortion_Fragments::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	switch (typeOfPickUp)
	{
	case EPickupType::DistortionFragments:
		UI_Data_Container->incrementD_FragCount(fragmentValue);
		break;

	case EPickupType::TimeAbilityShards:
		UI_Data_Container->incrementTA_FragCount();
		break;

	case EPickupType::Lives:
		UI_Data_Container->incrementLifeCount();
	}
	Cast<AAvatar>(OtherActor)->activateSoundFromDestroyedActor(9);
	Destroy();
}

