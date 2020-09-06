// Fill out your copyright notice in the Description page of Project Settings.


#include "Collsion_Actor_Component.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UCollsion_Actor_Component::UCollsion_Actor_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UCollsion_Actor_Component::UCollsion_Actor_Component(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our base mesh"));
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &UCollsion_Actor_Component::Collision);
}

UCollsion_Actor_Component::~UCollsion_Actor_Component()
{
	mesh = nullptr;
	triggerBox = nullptr;

	delete mesh;
	delete triggerBox;
}

// Called when the game starts
void UCollsion_Actor_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollsion_Actor_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollsion_Actor_Component::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue,"Your COMPONENT COLLIDER WORKS");
}

