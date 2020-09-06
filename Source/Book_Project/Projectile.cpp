// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
AProjectile::AProjectile(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	mesh->AttachTo(RootComponent);
	projectileCollider->AttachTo(mesh);
	projectileCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::Collision);
}
AProjectile::~AProjectile()
{
	projectileCollider = nullptr;
	mesh = nullptr;
	delete projectileCollider;
	delete mesh;
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	player= Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GetWorldTimerManager().SetTimer(moveTimer,this,&AProjectile::moveForward,callSpeed,true,0.0f);
	life = 0.f;
	
}

void AProjectile::moveForward()
{
	FVector forward;
	switch (typeOfProjectile)
	{
		case EProjectileType::Standard:
			forward = GetActorForwardVector();
			SetActorLocation(GetActorLocation() + (forward * speed));

			life += callSpeed;

			if (life >= lifeTime)
			{
				GetWorldTimerManager().ClearTimer(moveTimer);
				Destroy();
			}
			break;
		
		case EProjectileType::Tracking:
			FRotator lookAtPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());
			SetActorRotation(lookAtPlayer);
			forward = GetActorForwardVector();
			SetActorLocation(GetActorLocation() + forward*amountToMove);
			
			life += callSpeed;

			if (life >= lifeTime)
			{
				GetWorldTimerManager().ClearTimer(moveTimer);
				Destroy();
			}
			break;
	}
}

void AProjectile::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	if (player == nullptr)
	{
		return;
	}
	player->MinusHealth(damage);
	GetWorldTimerManager().ClearTimer(moveTimer);
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

