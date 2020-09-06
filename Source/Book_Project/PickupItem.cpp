// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "NPC_HUD.h"
#include "Engine/Engine.h"
// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "Unknown Item";
	Quantity = 0;
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Item Sphere Collider"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
	Mesh->AttachTo(RootComponent);
	ProxSphere->AttachTo(Mesh);
	Mesh->SetSimulatePhysics(true);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
}

void APickupItem::Prox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}

	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//avatar->Pickup(this);

	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	ANPC_HUD* hud = Cast<ANPC_HUD>(PController->GetHUD());

	GEngine->AddOnScreenDebugMessage(0, 7.f, FColor::Blue, "Picked up" + FString::FromInt(Quantity) + " " + Name);
	//avatar->printContentsOfBackpackOnScreen();
	Destroy();
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

