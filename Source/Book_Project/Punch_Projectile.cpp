// Fill out your copyright notice in the Description page of Project Settings.


#include "Punch_Projectile.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Avatar.h"
// Sets default values
APunch_Projectile::APunch_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APunch_Projectile::APunch_Projectile(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	mesh->AttachTo(RootComponent);
	projectileCollider->AttachTo(mesh);
	projectileCollider->OnComponentBeginOverlap.AddDynamic(this, &APunch_Projectile::Collision);
}

// Called when the game starts or when spawned
void APunch_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void APunch_Projectile::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor))
	{
		return;
	}
	if (Cast<AEnemyCharacter>(OtherActor) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,4.f,FColor::Emerald,"We hit that dastadly dangerous enemy");

		showColorVisual(Cast<AEnemyCharacter>(OtherActor));
		
		Cast<AEnemyCharacter>(OtherActor)->initiateDestruction(GetActorRotation());

		AAvatar* player=Cast<AAvatar>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatar::StaticClass()));

		player->activateSoundFromDestroyedActor(7);

		Destroy();
	}
}

// Called every frame
void APunch_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeAlive += DeltaTime;
	if (timeAlive >= lifetime)
	{
		Destroy();
	}

	SetActorLocation(GetActorLocation() + GetActorForwardVector()*speed);

}

